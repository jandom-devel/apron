/*
 * ptope_fun.h
 *
 * Direct access to hi-level parallelotope functions bypassing the manager.
 * The only file you need to include to use parallelotopes.
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

#ifndef __PTOPE_FUN_H
#define __PTOPE_FUN_H


/* dependencies */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define NUMFLT_PRINT_PREC ap_scalar_print_prec

#include "num.h"
#include "bound.h"

#include "ap_coeff.h"
#include "ap_dimension.h"
#include "ap_expr0.h"
#include "ap_manager.h"
#include "ptope.h"

#ifdef __cplusplus
extern "C" {
#endif



/* ============================================================ */
/* I.1 Memory */
/* ============================================================ */

struct _ptope_t;
typedef struct _ptope_t ptope_t;
  /* Abstract data type of parallelotopes (defined in ptope_internal.h). */

ptope_t* ptope_copy(ap_manager_t* man, ptope_t* a);
  /* Return a copy of an abstract value, on
     which destructive update does not affect the initial value. */

void ptope_free(ap_manager_t* man, ptope_t* a);
  /* Free all the memory used by the abstract value */

size_t ptope_size(ap_manager_t* man, ptope_t* a);
  /* Return the abstract size of an abstract value (see ap_manager_t) */


struct _ptope_internal_t;
typedef struct _ptope_internal_t ptope_internal_t;
  /* Abstract data type of library-specific manager options. */


ptope_t*          ptope_of_abstract0(ap_abstract0_t* a);
ap_abstract0_t* abstract0_of_ptope(ap_manager_t* man, ptope_t* ptope);
  /* Wrapping / unwrapping of ptope_t in ap_abstract0_t (no copy) */


/* ============================================================ */
/* I.2 Control of internal representation */
/* ============================================================ */

/* NOT IMPLEMENTED */

void ptope_minimize(ap_manager_t* man, ptope_t* a);

void ptope_canonicalize(ap_manager_t* man, ptope_t* a);

int ptope_hash(ap_manager_t* man, ptope_t* a);

void ptope_approximate(ap_manager_t* man, ptope_t* a, int algorithm);

bool ptope_is_minimal(ap_manager_t* man, ptope_t* a);

bool ptope_is_canonical(ap_manager_t* man, ptope_t* a);



/* ============================================================ */
/* I.3 Printing */
/* ============================================================ */

void ptope_fprint(FILE* stream,
		ap_manager_t* man,
		ptope_t* a,
		char** name_of_dim);
  /* Print the abstract value in a pretty way, using function
     name_of_dim to name dimensions */

void ptope_fprintdiff(FILE* stream,
		    ap_manager_t* man,
		    ptope_t* a1, ptope_t* a2,
		    char** name_of_dim);
  /* Print the difference between a1 (old value) and a2 (new value),
     using function name_of_dim to name dimensions.
     The meaning of difference is library dependent. */

void ptope_fdump(FILE* stream, ap_manager_t* man, ptope_t* a);
  /* Dump the internal representation of an abstract value,
     for debugging purposes */


/* ============================================================ */
/* I.4 Serialization */
/* ============================================================ */

ap_membuf_t ptope_serialize_raw(ap_manager_t* man, ptope_t* a);
/* Allocate a memory buffer (with malloc), output the abstract value in raw
   binary format to it and return a pointer on the memory buffer and the size
   of bytes written.  It is the user responsability to free the memory
   afterwards (with free). */

ptope_t* ptope_deserialize_raw(ap_manager_t* man, void* ptr, size_t* size);
/* Return the abstract value read in raw binary format from the input stream
   and store in size the number of bytes read */


/* ********************************************************************** */
/* II. Constructor, accessors, tests and property extraction */
/* ********************************************************************** */

/* ============================================================ */
/* II.1 Basic constructors */
/* ============================================================ */

/* We assume that dimensions [0..intdim-1] correspond to integer variables, and
   dimensions [intdim..intdim+realdim-1] to real variables */

ptope_t* ptope_bottom(ap_manager_t* man, size_t intdim, size_t realdim);
  /* Create a bottom (empty) value */

ptope_t* ptope_top(ap_manager_t* man, size_t intdim, size_t realdim);
  /* Create a top (universe) value */


ptope_t* ptope_of_box(ap_manager_t* man,
		  size_t intdim, size_t realdim,
		  ap_interval_t** tinterval);
  /* Abstract an hypercube defined by the array of intervals
     of size intdim+realdim */

ptope_t* ptope_of_lincons_array(ap_manager_t* man,
			      size_t intdim, size_t realdim,
			      ap_lincons0_array_t* array);
  /* Abstract a convex polyhedra defined by an array of linear constraints */

ptope_t* ptope_of_tcons_array(ap_manager_t* man,
			  size_t intdim, size_t realdim,
			  ap_tcons0_array_t* array);
  /* Abstract a conjunction of tree expressions constraints */

ptope_t* ptope_of_generator_array(ap_manager_t* man,
			      size_t intdim, size_t realdim,
			      ap_generator0_array_t* array);
  /* Abstract a convex polyhedra defined an array of generators */


/* ============================================================ */
/* II.2 Accessors */
/* ============================================================ */

ap_dimension_t ptope_dimension(ap_manager_t* man, ptope_t* a);
/* Return the total number of dimensions of the abstract values */


/* ============================================================ */
/* II.3 Tests */
/* ============================================================ */

bool ptope_is_bottom(ap_manager_t* man, ptope_t* a);
bool ptope_is_top(ap_manager_t* man, ptope_t* a);

bool ptope_is_leq(ap_manager_t* man, ptope_t* a1, ptope_t* a2);
  /* inclusion check */

bool ptope_is_eq(ap_manager_t* man, ptope_t* a1, ptope_t* a2);
  /* equality check */

/* NOT IMPLEMENTED */
bool ptope_sat_lincons(ap_manager_t* man, ptope_t* a, ap_lincons0_t* cons);
  /* does the abstract value satisfy the linear constraint ? */

bool ptope_sat_tcons(ap_manager_t* man, ptope_t* a, ap_tcons0_t* cons);
  /* does the abstract value satisfy the tree expression constraint ? */

bool ptope_sat_interval(ap_manager_t* man, ptope_t* a,
		      ap_dim_t dim, ap_interval_t* interval);
  /* is the dimension included in the interval in the abstract value ? */

bool ptope_is_dimension_unconstrained(ap_manager_t* man, ptope_t* a,
				    ap_dim_t dim);
  /* is the dimension unconstrained ? */

/* ============================================================ */
/* II.4 Extraction of properties */
/* ============================================================ */

ap_interval_t* ptope_bound_linexpr(ap_manager_t* man,
				 ptope_t* a, ap_linexpr0_t* expr);
  /* Returns the interval taken by a linear expression
     over the abstract value */

ap_interval_t* ptope_bound_texpr(ap_manager_t* man,
			       ptope_t* a, ap_texpr0_t* expr);
  /* Returns the interval taken by a tree expression
     over the abstract value */

ap_interval_t* ptope_bound_dimension(ap_manager_t* man,
				   ptope_t* a, ap_dim_t dim);
  /* Returns the interval taken by the dimension
     over the abstract value */

ap_lincons0_array_t ptope_to_lincons_array(ap_manager_t* man, ptope_t* a);
  /* Converts an abstract value to a polyhedra
     (conjunction of linear constraints). */

ap_tcons0_array_t ptope_to_tcons_array(ap_manager_t* man, ptope_t* a);
  /* Converts an abstract value to a conjunction
     of tree expressions constraints */

ap_interval_t** ptope_to_box(ap_manager_t* man, ptope_t* a);
  /* Converts an abstract value to an interval/hypercube.
     The size of the resulting array is ptope_dimension(man,a).  This
     function can be reimplemented by using ptope_bound_linexpr */

ap_generator0_array_t ptope_to_generator_array(ap_manager_t* man, ptope_t* a);
  /* Converts an abstract value to a system of generators. */


/* ********************************************************************** */
/* III. Operations */
/* ********************************************************************** */

/* ============================================================ */
/* III.1 Meet and Join */
/* ============================================================ */

ptope_t* ptope_meet(ap_manager_t* man, bool destructive, ptope_t* a1, ptope_t* a2);
ptope_t* ptope_join(ap_manager_t* man, bool destructive, ptope_t* a1, ptope_t* a2);
  /* Meet and Join of 2 abstract values */

ptope_t* ptope_meet_array(ap_manager_t* man, ptope_t** tab, size_t size);
ptope_t* ptope_join_array(ap_manager_t* man, ptope_t** tab, size_t size);
  /* Meet and Join of an array of abstract values.
     Raises an [[exc_invalid_argument]] exception if [[size==0]]
     (no way to define the dimensionality of the result in such a case */

ptope_t* ptope_meet_lincons_array(ap_manager_t* man,
			      bool destructive, ptope_t* a,
			      ap_lincons0_array_t* array);
  /* Meet of an abstract value with a set of constraints
     (generalize ptope_of_lincons_array) */

ptope_t* ptope_meet_tcons_array(ap_manager_t* man,
			    bool destructive, ptope_t* a,
			    ap_tcons0_array_t* array);
  /* Meet of an abstract value with a set of tree expressions constraints.
     (generalize ptope_of_tcons_array) */

ptope_t* ptope_add_ray_array(ap_manager_t* man,
			 bool destructive, ptope_t* a,
			 ap_generator0_array_t* array);
  /* Generalized time elapse operator.
     Note: this is not like adding arbitrary generators because:
     - ptope_add_ray_array is strict
     - array can only contain rays and lines, not vertices
   */

/* ============================================================ */
/* III.2 Assignement and Substitutions */
/* ============================================================ */

ptope_t* ptope_assign_linexpr_array(ap_manager_t* man,
				bool destructive, ptope_t* a,
				ap_dim_t* tdim,
				ap_linexpr0_t** texpr,
				size_t size,
				ptope_t* dest);
ptope_t* ptope_substitute_linexpr_array(ap_manager_t* man,
				    bool destructive, ptope_t* a,
				    ap_dim_t* tdim,
				    ap_linexpr0_t** texpr,
				    size_t size,
				    ptope_t* dest);
ptope_t* ptope_assign_texpr_array(ap_manager_t* man,
			      bool destructive, ptope_t* a,
			      ap_dim_t* tdim,
			      ap_texpr0_t** texpr,
			      size_t size,
			      ptope_t* dest);
ptope_t* ptope_substitute_texpr_array(ap_manager_t* man,
				  bool destructive, ptope_t* a,
				  ap_dim_t* tdim,
				  ap_texpr0_t** texpr,
				  size_t size,
				  ptope_t* dest);


  /* Parallel Assignement and Substitution of several dimensions by
     expressions in abstract value org.

     dest is an optional argument. If not NULL, semantically speaking,
     the result of the transformation is intersected with dest. This is
     useful for precise backward transformations in lattices like intervals or
     parallelotopes. */

/* ============================================================ */
/* III.3 Projections */
/* ============================================================ */

ptope_t* ptope_forget_array(ap_manager_t* man,
			bool destructive, ptope_t* a,
			ap_dim_t* tdim, size_t size,
			bool project);

/* ============================================================ */
/* III.4 Change and permutation of dimensions */
/* ============================================================ */

ptope_t* ptope_add_dimensions(ap_manager_t* man,
			  bool destructive, ptope_t* a,
			  ap_dimchange_t* dimchange,
			  bool project);

ptope_t* ptope_remove_dimensions(ap_manager_t* man,
			     bool destructive, ptope_t* a,
			     ap_dimchange_t* dimchange);

ptope_t* ptope_permute_dimensions(ap_manager_t* man,
			      bool destructive,
			      ptope_t* a,
			      ap_dimperm_t* permutation);

/* ============================================================ */
/* III.5 Expansion and folding of dimensions */
/* ============================================================ */

ptope_t* ptope_expand(ap_manager_t* man,
		  bool destructive, ptope_t* a,
		  ap_dim_t dim,
		  size_t n);
  /* Expand the dimension dim into itself + n additional dimensions.
     It results in (n+1) unrelated dimensions having same
     relations with other dimensions. The (n+1) dimensions are put as follows:

     - original dimension dim

     - if the dimension is integer, the n additional dimensions are put at the
       end of integer dimensions; if it is real, at the end of the real
       dimensions.
  */

ptope_t* ptope_fold(ap_manager_t* man,
		bool destructive, ptope_t* a,
		ap_dim_t* tdim,
		size_t size);
  /* Fold the dimensions in the array tdim of size n>=1 and put the result
     in the first dimension in the array. The other dimensions of the array
     are then removed. */

/* ============================================================ */
/* III.6 Widening, Narrowing */
/* ============================================================ */

ptope_t* ptope_widening(ap_manager_t* man, ptope_t* a1, ptope_t* a2);
  /* Standard widening: set unstable constraints to +oo */

ptope_t* ptope_widening_thresholds(ap_manager_t* man,
			       ptope_t* a1, ptope_t* a2,
			       ap_scalar_t** array,
			       size_t nb);
  /* Widening with threshold.
     array is assumed to contain nb thresholds, sorted in increasing order. */

ptope_t* ptope_narrowing(ap_manager_t* man, ptope_t* a1, ptope_t* a2);
  /* Standard narrowing: refine only +oo constraint */

ptope_t* ptope_add_epsilon(ap_manager_t* man, ptope_t* a, ap_scalar_t* epsilon);
  /* Enlarge each bound by epsilon times the maximum finite bound in
     the parallelotopes */

ptope_t* ptope_add_epsilon_bin(ap_manager_t* man, ptope_t* a1, ptope_t* a2,
			   ap_scalar_t* epsilon);
  /* Enlarge each bound from a1 by epsilon times the maximum finite bound in
     a2. Only bounds in a1 that are not stable in a2 are enlarged. */


/* ============================================================ */
/* III.7 Topological closure operation */
/* ============================================================ */

ptope_t* ptope_closure(ap_manager_t* man, bool destructive, ptope_t* a);
  /* Returns the topological closure of a possibly opened abstract value */


#ifdef __cplusplus
}
#endif

#endif /* __ptope_FUN_H */
