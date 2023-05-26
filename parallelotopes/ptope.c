/*
 * ptope.c
 *
 * Implementation of the parallelotope domain.
 *
 * APRON Library / Parallelotope Domain
 *
 * Copyright (C) Gianluca Amato and Francesca Scozzari 2023
 *
 */

/* This file is part of the APRON Library, released under LGPL license
   with an exception allowing the redistribution of statically linked
   executables.

   Please read the COPYING file packaged in the distribution.
*/

#include "ptope.h"
#include "ptope_internal.h"
#include "ap_generic.h"

/* ============================================================ */
/* Managers */
/* ============================================================ */

void ptope_internal_free(ptope_internal_t* pr)
{
  bound_clear_array(pr->tmp,pr->tmp_size);
  free(pr->tmp);
  free(pr->tmp2);
  free(pr);
}

ap_manager_t* ptope_manager_alloc(void)
{
  size_t i;
  ap_manager_t* man;
  ptope_internal_t* pr;

  if (!ap_fpu_init()) {
    fprintf(stderr,"ptope_manager_alloc cannot change the FPU rounding mode\n");
  }

  pr = (ptope_internal_t*)malloc(sizeof(ptope_internal_t));
  assert(pr);
  pr->tmp_size = 10;
  pr->tmp = malloc(sizeof(bound_t)*pr->tmp_size);
  assert(pr->tmp);
  bound_init_array(pr->tmp,pr->tmp_size);
  pr->tmp2 = malloc(sizeof(long)*pr->tmp_size);
  assert(pr->tmp2);

  man = ap_manager_alloc("ptope","1.0 with " NUM_NAME, pr,
			 (void (*)(void*))ptope_internal_free);

  pr->man = man;

  man->funptr[AP_FUNID_COPY] = &ptope_copy;
  man->funptr[AP_FUNID_FREE] = &ptope_free;
  man->funptr[AP_FUNID_ASIZE] = &ptope_size;
  man->funptr[AP_FUNID_MINIMIZE] = &ptope_minimize;
  man->funptr[AP_FUNID_CANONICALIZE] = &ptope_canonicalize;
  man->funptr[AP_FUNID_HASH] = &ptope_hash;
  man->funptr[AP_FUNID_APPROXIMATE] = &ptope_approximate;
  man->funptr[AP_FUNID_FPRINT] = &ptope_fprint;
  man->funptr[AP_FUNID_FPRINTDIFF] = &ptope_fprintdiff;
  man->funptr[AP_FUNID_FDUMP] = &ptope_fdump;
  man->funptr[AP_FUNID_SERIALIZE_RAW] = &ptope_serialize_raw;
  man->funptr[AP_FUNID_DESERIALIZE_RAW] = &ptope_deserialize_raw;
  man->funptr[AP_FUNID_BOTTOM] = &ptope_bottom;
  man->funptr[AP_FUNID_TOP] = &ptope_top;
  man->funptr[AP_FUNID_OF_BOX] = &ptope_of_box;
  man->funptr[AP_FUNID_DIMENSION] = &ptope_dimension;
  man->funptr[AP_FUNID_IS_BOTTOM] = &ptope_is_bottom;
  man->funptr[AP_FUNID_IS_TOP] = &ptope_is_top;
  man->funptr[AP_FUNID_IS_LEQ] = &ptope_is_leq;
  man->funptr[AP_FUNID_IS_EQ] = &ptope_is_eq;
  man->funptr[AP_FUNID_IS_DIMENSION_UNCONSTRAINED] = &ptope_is_dimension_unconstrained;
  man->funptr[AP_FUNID_SAT_INTERVAL] = &ptope_sat_interval;
  man->funptr[AP_FUNID_SAT_LINCONS] = &ptope_sat_lincons;
  man->funptr[AP_FUNID_SAT_TCONS] = &ptope_sat_tcons;
  man->funptr[AP_FUNID_BOUND_DIMENSION] = &ptope_bound_dimension;
  man->funptr[AP_FUNID_BOUND_LINEXPR] = &ptope_bound_linexpr;
  man->funptr[AP_FUNID_BOUND_TEXPR] = &ptope_bound_texpr;
  man->funptr[AP_FUNID_TO_BOX] = &ptope_to_box;
  man->funptr[AP_FUNID_TO_LINCONS_ARRAY] = &ptope_to_lincons_array;
  man->funptr[AP_FUNID_TO_TCONS_ARRAY] = &ptope_to_tcons_array;
  man->funptr[AP_FUNID_TO_GENERATOR_ARRAY] = &ptope_to_generator_array;
  man->funptr[AP_FUNID_MEET] = &ptope_meet;
  man->funptr[AP_FUNID_MEET_ARRAY] = &ptope_meet_array;
  man->funptr[AP_FUNID_MEET_LINCONS_ARRAY] = &ptope_meet_lincons_array;
  man->funptr[AP_FUNID_MEET_TCONS_ARRAY] = &ptope_meet_tcons_array;
  man->funptr[AP_FUNID_JOIN] = &ptope_join;
  man->funptr[AP_FUNID_JOIN_ARRAY] = &ptope_join_array;
  man->funptr[AP_FUNID_ADD_RAY_ARRAY] = &ptope_add_ray_array;
  man->funptr[AP_FUNID_ASSIGN_LINEXPR_ARRAY] = &ptope_assign_linexpr_array;
  man->funptr[AP_FUNID_SUBSTITUTE_LINEXPR_ARRAY] = &ptope_substitute_linexpr_array;
  man->funptr[AP_FUNID_ASSIGN_TEXPR_ARRAY] = &ptope_assign_texpr_array;
  man->funptr[AP_FUNID_SUBSTITUTE_TEXPR_ARRAY] = &ptope_substitute_texpr_array;
  man->funptr[AP_FUNID_ADD_DIMENSIONS] = &ptope_add_dimensions;
  man->funptr[AP_FUNID_REMOVE_DIMENSIONS] = &ptope_remove_dimensions;
  man->funptr[AP_FUNID_PERMUTE_DIMENSIONS] = &ptope_permute_dimensions;
  man->funptr[AP_FUNID_FORGET_ARRAY] = &ptope_forget_array;
  man->funptr[AP_FUNID_EXPAND] = &ptope_expand;
  man->funptr[AP_FUNID_FOLD] = &ptope_fold;
  man->funptr[AP_FUNID_WIDENING] = &ptope_widening;
  man->funptr[AP_FUNID_CLOSURE] = &ptope_closure;

  for (i=0;i<AP_EXC_SIZE;i++)
    ap_manager_set_abort_if_exception(man,i,false);

  return man;
}

ptope_t* ptope_of_abstract0(ap_abstract0_t* a)
{
  return (ptope_t*)a->value;
}

ap_abstract0_t* abstract0_of_ptope(ap_manager_t* man, ptope_t* ptope)
{
  ap_abstract0_t* r = malloc(sizeof(ap_abstract0_t));
  assert(r);
  r->value = ptope;
  r->man = ap_manager_copy(man);
  return r;
}
