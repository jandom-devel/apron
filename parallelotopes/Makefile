# Makefile
#
# APRON Library / Parallelotope Domain
#
# Copyright (C) Gianluca Amato and Francesca Scozzari 2023

# This file is part of the APRON Library, released under LGPL license
# with an exemption allowing the redistribution of statically linked
# executables.
#
# Please read the COPYING file packaged in the distribution.

include ../Makefile.config
include ../vars.mk

#---------------------------------------
# Programs
#---------------------------------------

#---------------------------------------
# Flags
#---------------------------------------

ICFLAGS += $(BASE_ICFLAGS) $(ML_ICFLAGS)
LDFLAGS += $(BASE_LIFLAGS)
CMXSINC = $(APRON_CMXSINC) -I .

#---------------------------------------
# Files
#---------------------------------------

CCSOURCES = ptope.c

CCINC = ptope_internal.h ptope_fun.h

# trigers a whole recompilation
#DEPS = $(APRON_INCLUDE)/ap_abstract0.h

LIBS = -lapron -lmpfr -lgmp -lm
LIBS_DEBUG = -lapron_debug -lmpfr -lgmp -lm

#---------------------------------------
# Rules
#---------------------------------------

root:
	@echo
	@echo "Please choose a target from:"
	@echo
	@echo " Il Ill MPZ Rl Rll MPQ D Dl MPFR: single C library"
	@echo " all                     : all C libraries"
	@echo " ml                      : OCaml library"
	@echo " mlIl mlIll ...          : OCaml toplevel & byte-code"
	@echo " allml                   : everything"
	@echo " clean                   : remove objects"
	@echo " install                 : to install what has been compiled"
	@echo " uninstall               : clean & uninstall"
	@echo

all: Il Ill MPZ Ri Rll MPQ D Dl MPFR
allml: allIl allIll allMPZ allRi allRll allMPQ allD allDl allMPFR

allIl: Il mlIl
allIll: Ill mlIll
allMPZ: MPZ mlMPZ
allRi: Ri mlRi
allRll: Rll mlRll
allMPQ: MPQ mlMPQ
allD: D mlD
allDl: Dl mlDl
allMPFR: MPFR mlMPFR

Il: libptopeIl.a libptopeIl_debug.a ptopetestIl
Ill: libptopeIll.a libptopeIll_debug.a ptopetestIll
MPZ: libptopeMPZ.a libptopeMPZ_debug.a ptopetestMPZ
Ri: libptopeRi.a libptopeRi_debug.a ptopetestRi
Rll: libptopeRll.a libptopeRll_debug.a ptopetestRll
MPQ: libptopeMPQ.a libptopeMPQ_debug.a ptopetestMPQ
D: libptopeD.a libptopeD_debug.a ptopetestD
Dl: libptopeDl.a libptopeDl_debug.a ptopetestDl
MPFR: libptopeMPFR.a libptopeMPFR_debug.a ptopetestMPFR
ifneq ($(HAS_SHARED),)
Il: libptopeIl.$(EXT_DLL) libptopeIl_debug.$(EXT_DLL)
Ill: libptopeIll.$(EXT_DLL) libptopeIll_debug.$(EXT_DLL)
MPZ: libptopeMPZ.$(EXT_DLL) libptopeMPZ_debug.$(EXT_DLL)
Ri: libptopeRi.$(EXT_DLL) libptopeRi_debug.$(EXT_DLL)
Rll: libptopeRll.$(EXT_DLL) libptopeRll_debug.$(EXT_DLL)
MPQ: libptopeMPQ.$(EXT_DLL) libptopeMPQ_debug.$(EXT_DLL)
D: libptopeD.$(EXT_DLL) libptopeD_debug.$(EXT_DLL)
Dl: libptopeDl.$(EXT_DLL) libptopeDl_debug.$(EXT_DLL)
MPFR: libptopeMPFR.$(EXT_DLL) libptopeMPFR_debug.$(EXT_DLL)
endif

mlexample%.byte: mlexample.ml ptope%.cma
	$(OCAMLC) $(OCAMLFLAGS) -I $(MLGMPIDL_LIB) -I $(APRON_LIB) -o $@ bigarray.cma gmp.cma apron.cma ptope$*.cma $<

mlexample%.opt: mlexample.ml ptope%.cmxa
	$(OCAMLOPT) $(OCAMLOPTFLAGS) -I $(MLGMPIDL_LIB) -I $(APRON_LIB) -o $@ bigarray.cmxa gmp.cmxa apron.cmxa ptope$*.cmxa $<

clean:
	/bin/rm -f *.[ao] *.$(EXT_DLL) ptopetest*
	/bin/rm -f *.?.tex *.log *.aux *.bbl *.blg *.toc *.dvi *.ps *.pstex*
	/bin/rm -fr *.annot *.cm[ioax] *.cmx[as]
	/bin/rm -fr ptopetop* ptoperun* tmp
	/bin/rm -fr *~ \#*\#
	/bin/rm -fr ptope_caml.c ptope.ml ptope.mli
	/bin/rm -f Makefile.depend

distclean: clean

install:
	$(INSTALLd) $(APRON_INCLUDE) $(APRON_INCLUDE)/ptope $(APRON_LIB) $(APRON_BIN)
	$(INSTALL) ptope.h $(APRON_INCLUDE)
	$(INSTALL) $(CCINC) $(APRON_INCLUDE)/ptope
	for i in ptopetest* ptopetop* ptoperun*; do \
		if test -f $$i; then $(INSTALL) $$i $(APRON_BIN); fi; \
	done
	for i in libptope*.* libptope*_debug.*; do \
		if test -f $$i; then $(INSTALL) $$i $(APRON_LIB); fi; \
	done
ifeq ($(OCAMLFIND),)
	for i in libptope*_caml.* dllptope*_caml.$(EXT_DLL); do \
		if test -f $$i; then $(INSTALL) $$i $(APRON_LIB); fi; \
	done
	for i in ptope.idl ptope.mli ptope.cmi ptope.cmx ptope*.cma ptope*.cmxa ptope*.a; do \
		if test -f $$i; then $(INSTALL) $$i $(APRON_LIB); fi; \
	done
endif

uninstall:
	/bin/rm -fr $(APRON_INCLUDE)/ptope.h
	/bin/rm -fr $(APRON_INCLUDE)/ptope
	/bin/rm -f $(APRON_BIN)/ptopetest* $(APRON_BIN)/ptopetop* $(APRON_BIN)/ptoperun*
	/bin/rm -f $(APRON_LIB)/libptope*.* $(APRON_LIB)/libptope*_debug.*
	/bin/rm -f $(APRON_LIB)/dllptope*.$(EXT_DLL) $(APRON_LIB)/dllptope*_debug.$(EXT_DLL)
	/bin/rm -f $(APRON_LIB)/ptope.mli $(APRON_LIB)/ptope.cm[ix] $(APRON_LIB)/ptope.idl $(APRON_LIB)/ptope*.cma $(APRON_LIB)/ptope*.cmx[as] $(APRON_LIB)/ptope*.a

dist: Makefile COPYING README ptope_doc.html perlscript_caml.pl perlscript_c.pl $(CCSOURCES) $(CCINC) ptope.h ptope_test.c ptope.idl ptope.mli ptope.ml ptope_caml.c
	(cd ..; tar zcvf ptopeagons.tgz $(^:%=ptopeagons/%))

#---------------------------------------
# IMPLICIT RULES AND DEPENDENCIES
#---------------------------------------

.SUFFIXES: .tex .c .h .a .o .$(EXT_DLL)

#-----------------------------------
# C part
#-----------------------------------

libptope%.a: $(subst .c,%.o,$(CCSOURCES))
	$(AR) rcs $@ $^
	$(RANLIB) $@

libptope%_debug.a: $(subst .c,%_debug.o,$(CCSOURCES))
	$(AR) rcs $@ $^
	$(RANLIB) $@

libptope%.$(EXT_DLL): $(subst .c,%.o,$(CCSOURCES))
	$(CC_APRON_DYLIB) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

libptope%_debug.$(EXT_DLL): $(subst .c,%_debug.o,$(CCSOURCES))
	$(CC_APRON_DYLIB) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS_DEBUG)

ifneq ($(HAS_SHARED),)
ptopetest%: ptope_test%.o libptope%_debug.a libptope%_debug.$(EXT_DLL)
else
ptopetest%: ptope_test%.o libptope%_debug.a
endif
	$(CC) -o $@ ptope_test$*.o \
		-L. -lptope$*_debug -L../newpolka -lpolkaMPQ_debug \
		$(LDFLAGS) $(LIBS_DEBUG) $(CFLAGS_DEBUG)

%_caml.o: %_caml.c $(CCINC) $(DEPS)
	$(CC) $(CFLAGS) $(ICFLAGS) -c -o $@ $<

%_caml_debug.o: %_caml.c $(CCINC) $(DEPS)
	$(CC) $(CFLAGS_DEBUG) $(ICFLAGS) -c -o $@ $<

%Il.o: %.c $(CCINC) $(DEPS)
	$(CC) $(CFLAGS) $(ICFLAGS) -DNUM_LONGINT -c -o $@ $<
%Il_debug.o: %.c $(CCINC) $(DEPS)
	$(CC) $(CFLAGS_DEBUG) $(ICFLAGS) -DNUM_LONGINT -c -o $@ $<
%Ill.o: %.c $(CCINC) $(DEPS)
	$(CC) $(CFLAGS) $(ICFLAGS) -DNUM_LONGLONGINT -c -o $@ $<
%Ill_debug.o: %.c $(CCINC) $(DEPS)
	$(CC) $(CFLAGS_DEBUG) $(ICFLAGS) -DNUM_LONGLONGINT -c -o $@ $<
%MPZ.o: %.c $(CCINC) $(DEPS)
	$(CC) $(CFLAGS) $(ICFLAGS) -DNUM_MPZ -c -o $@ $<
%MPZ_debug.o: %.c $(CCINC) $(DEPS)
	$(CC) $(CFLAGS_DEBUG) $(ICFLAGS) -DNUM_MPZ -c -o $@ $<

%Ri.o: %.c $(CCINC) $(DEPS)
	$(CC) $(CFLAGS) $(ICFLAGS) -DNUM_LONGRAT -c -o $@ $<
%Ri_debug.o: %.c $(CCINC) $(DEPS)
	$(CC) $(CFLAGS_DEBUG) $(ICFLAGS) -DNUM_LONGRAT -c -o $@ $<
%Rll.o: %.c $(CCINC) $(DEPS)
	$(CC) $(CFLAGS) $(ICFLAGS) -DNUM_LONGLONGRAT -c -o $@ $<
%Rll_debug.o: %.c $(CCINC) $(DEPS)
	$(CC) $(CFLAGS_DEBUG) $(ICFLAGS) -DNUM_LONGLONGRAT -c -o $@ $<
%MPQ.o: %.c $(CCINC) $(DEPS)
	$(CC) $(CFLAGS) $(ICFLAGS) -DNUM_MPQ -c -o $@ $<
%MPQ_debug.o: %.c $(CCINC) $(DEPS)
	$(CC) $(CFLAGS_DEBUG) $(ICFLAGS) -DNUM_MPQ -c -o $@ $<

%D.o: %.c $(CCINC) $(DEPS)
	$(CC) $(CFLAGS) $(ICFLAGS) -DNUM_DOUBLE -c -o $@ $<
%D_debug.o: %.c $(CCINC) $(DEPS)
	$(CC) $(CFLAGS) $(ICFLAGS) -DNUM_DOUBLE -c -o $@ $<
%Dl.o: %.c $(CCINC) $(DEPS)
	$(CC) $(CFLAGS) $(ICFLAGS) -DNUM_LONGDOUBLE -c -o $@ $<
%Dl_debug.o: %.c $(CCINC) $(DEPS)
	$(CC) $(CFLAGS) $(ICFLAGS) -DNUM_LONGDOUBLE -c -o $@ $<
%MPFR.o: %.c $(CCINC) $(DEPS)
	$(CC) $(CFLAGS) $(ICFLAGS) -DNUM_MPFR -c -o $@ $<
%MPFR_debug.o: %.c $(CCINC) $(DEPS)
	$(CC) $(CFLAGS) $(ICFLAGS) -DNUM_MPFR -c -o $@ $<

# TODO: mpfr ?

.PRECIOUS: libptope%.a libptope%_debug.a libptope%.$(EXT_DLL) libptope%_debug.$(EXT_DLL)
.PRECIOUS: libptope%_caml.a libptope%_caml_debug.a dllptope%_caml.$(EXT_DLL)
.PRECIOUS: %Il.o %Ill.o %MPZ.o %Ri.o %Rll.o %MPQ.o %D.o %Dl.o %MPFR.o
.PRECIOUS: %Il_debug.o %Ill_debug.o %MPZ_debug.o %Ri_debug.o %Rll_debug.o %MPQ_debug.o %D_debug.o %Dl_debug.o %MPFR_debug.o

#-----------------------------------
# Caml part
#-----------------------------------

.INTERMEDIATE: mlIl

ml: ptope.mli ptope.cmi
mlIl: ml ptopeIl.cma libptopeIl_caml.a libptopeIl_caml_debug.a
mlIll: ml ptopeIll.cma libptopeIll_caml.a libptopeIll_caml_debug.a
mlMPZ: ml ptopeMPZ.cma libptopeMPZ_caml.a libptopeMPZ_caml_debug.a
mlRi: ml ptopeRi.cma libptopeRi_caml.a libptopeRi_caml_debug.a
mlRll: ml ptopeRll.cma libptopeRll_caml.a libptopeRll_caml_debug.a
mlMPQ: ml ptopeMPQ.cma libptopeMPQ_caml.a libptopeMPQ_caml_debug.a
mlD: ml ptopeD.cma libptopeD_caml.a libptopeD_caml_debug.a
mlDl: ml ptopeDl.cma libptopeDl_caml.a libptopeDl_caml_debug.a
mlMPFR: ml ptopeMPFR.cma libptopeMPFR_caml.a libptopeMPFR_caml_debug.a
ifneq ($(HAS_OCAMLOPT),)
mlIl: $(call OCAMLOPT_TARGETS, ptopeIl)
mlIll: $(call OCAMLOPT_TARGETS, ptopeIll)
mlMPZ: $(call OCAMLOPT_TARGETS, ptopeMPZ)
mlRi: $(call OCAMLOPT_TARGETS, ptopeRi)
mlRll: $(call OCAMLOPT_TARGETS, ptopeRll)
mlMPQ: $(call OCAMLOPT_TARGETS, ptopeMPQ)
mlD: $(call OCAMLOPT_TARGETS, ptopeD)
mlDl: $(call OCAMLOPT_TARGETS, ptopeDl)
mlMPFR: $(call OCAMLOPT_TARGETS, ptopeMPFR)
endif
ifneq ($(HAS_SHARED),)
mlIl: dllptopeIl_caml.$(EXT_DLL)
mlIll:dllptopeIll_caml.$(EXT_DLL)
mlMPZ:dllptopeMPZ_caml.$(EXT_DLL)
mlRll:dllptopeRll_caml.$(EXT_DLL)
mlMPQ:dllptopeMPQ_caml.$(EXT_DLL)
mlD:dllptopeD_caml.$(EXT_DLL)
mlDl:dllptopeDl_caml.$(EXT_DLL)
mlMPFR:dllptopeMPFR_caml.$(EXT_DLL)
endif

#ptopetop%: ptope.cma libptope_caml.a libptope%.a
#	$(OCAMLMKTOP) -noautolink $(OCAMLFLAGS) $(OCAMLINC) -o $@ -custom bigarray.cma gmp.cma apron.cma ptope.cma -ccopt "-L. -L../mlapronidl $(LDFLAGS)" -cclib "-lptope_caml -lptope$* -lapron_caml -lapron -lgmp_caml -lmpfr -lgmp -lbigarray -lcamlidl"

#ptoperun%: ptope.cma libptope_caml.a
#	$(OCAMLC) -noautolink $(OCAMLFLAGS) $(OCAMLINC) -o $@ -make-runtime bigarray.cma gmp.cma apron.cma ptope.cma -ccopt "-L. -L../mlapronidl $(LDFLAGS)" -cclib "-lptope_caml -lptope$* -lapron_caml -lapron -lgmp_caml -lmpfr -lgmp -lbigarray -lcamlidl"

ptope%.cma: ptope.cmo libptope%_caml.a libptope%.a
	$(OCAMLMKLIB) -o ptope$* -oc ptope$*_caml ptope.cmo -lptope$* $(LIBS)

ptope%.cmxa ptope%.a: ptope.cmx libptope%_caml.a libptope%.a
	$(OCAMLMKLIB) -o ptope$* -oc ptope$*_caml ptope.cmx -lptope$* $(LIBS)

dllptope%_caml.$(EXT_DLL) libptope%_caml.a: ptope_caml.o libptope%.a
	$(OCAMLMKLIB) -o ptope$*_caml $< -L. -lptope$* $(LDFLAGS) $(LIBS)

dllptope%_caml_debug.$(EXT_DLL) libptope%_caml_debug.a: ptope_caml_debug.o libptope%_debug.a
	$(OCAMLMKLIB) -o ptope$*_caml_debug $< -L. -lptope$*_debug $(LDFLAGS) $(LIBS_DEBUG)

%.ml %.mli %_caml.c: %.idl perlscript_c.pl perlscript_caml.pl ../mlapronidl/*.idl
	mkdir -p tmp
	cp $*.idl ../mlapronidl/*.idl tmp
	cd tmp && $(CAMLIDL) -no-include -nocpp -I . $*.idl
	$(PERL) perlscript_c.pl < tmp/$*_stubs.c >$*_caml.c
	$(PERL) perlscript_caml.pl < tmp/$*.ml >$*.ml
	$(PERL) perlscript_caml.pl < tmp/$*.mli >$*.mli

rebuild:
	@echo "make rebuild is no longer necessary"

.PRECIOUS: %_caml.c %.ml %.mli %.cmi libptope%_caml.a libptope%_caml_debug.a dllptope%_caml.$(EXT_DLL) ptope.cmx ptope.cmo

#---------------------------------------
# ML generic rules
#---------------------------------------

%.cmi: %.mli  $(DEPS)
	$(OCAMLC) $(OCAMLFLAGS) $(OCAMLINC) -c $<

%.cmo: %.ml %.cmi  $(DEPS)
	$(OCAMLC) $(OCAMLFLAGS) $(OCAMLINC) -c $<

%.cmx: %.ml %.cmi  $(DEPS)
	$(OCAMLOPT) $(OCAMLOPTFLAGS) $(OCAMLINC) -c $<

%.cmxs: %.cmxa
	$(OCAMLOPT_CMXS) $(CMXSINC) -o $@ $<

#-----------------------------------
# DEPENDENCIES
#-----------------------------------
