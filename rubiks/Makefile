# Makefile for the Rubik's Cube Puzzle Project
#
# File:		Makefile
# Date:		Wed Mar 18 11:34:51 EDT 2015
# Author:	Thu Mar 19 01:40:32 EDT 2015
#
# The authors have placed this file in the public
# domain; they make no warranty and accept no liability
# for this file.

#   P		puzzle name
#   M		monitor name
#
#   XTRA_INPUTS	extra input files that must be granted
#		access
#   XTRA_LIBS	extra libraries for C and C++ programs
#   XTRA_LIMITS limits that override those given
#               previously to hpcm_sandbox
#   
P = rubiks
M = QA
XTRA_INPUTS =
XTRA_LIBS =
XTRA_LIMITS =
C_FLAGS = -O2 -std=c99
CC_FLAGS = -O2
JAVA_FLAGS = -g
CL_FLAGS = --script

TESTS= io rotation debug \
       search search-timing part-search \
       mitm mitm-long mitm-timing part-mitm

.SUFFIXES:
.SUFFIXES: .c .cc .java .lsp

.PRECIOUS:	$(TESTS:%=test-%.in) \
		$(TESTS:%=test-%.test)

default:	$P.out

.c:	rubiks.h rubiks_lib.o
	rm -f $* core core.[0-9]*
	gcc ${C_FLAGS} -o $* $*.c rubiks_lib.o \
	    -lstdc++ -lm -lcrypt ${XTRA_LIBS}

.cc:	rubiks.h rubiks_lib.o
	rm -f $* core core.[0-9]*
	g++ ${CC_FLAGS} -o $* $*.cc rubiks_lib.o \
	    -lm -lcrypt ${XTRA_LIBS}

.java:
	rm -f $* *.class core core.[0-9]*
	javac ${JAVA_FLAGS} $*.java
	echo >$* '#!/bin/sh'
	echo >>$* "exec `which java` -ea $* \$$*"
	chmod a+r *.class
	chmod a+rx $*

.lsp:
	rm -f $* core core.[0-9]*
	echo >$* '#!/bin/sh'
	echo >>$* "exec sbcl ${CL_FLAGS}" \
	          "$*.lsp" '"$$@"'
	chmod a+r $*.lsp
	f no files are given, the problem name with extechmod a+rx $*

#
test-%.in:
	cp sample-$*.in test-$*.in
	chmod u+rw test-$*.in

test-%.test:
	cp sample-$*.test test-$*.test
	chmod u+rw test-$*.test

test-%:	test-%.in test-%.test
	rm -f $P.in $P.out $P.test
	ln -s test-$*.in $P.in
	ln -s test-$*.test $P.test
	make --no-print-directory test

$P.out:	$P $P.in
	rm -f $P.out core core.[0-9]*
	grant_access . $P ${XTRA_INPUTS}
	$M hpcm_sandbox -datasize 1g \
			-space 1g \
		        -stacksize 64m \
		        ${XTRA_LIMITS} \
		        $P \
	    <$P.in | tee $P.out

test:	$P.out $P.test
	@echo ""
	@echo "DIFFERENCES: $P.test ---> $P.out"
	@if diff -u $P.test $P.out; \
	    then echo "NO DIFFERENCES FOUND"; fi

$P.debug:	$P $P.in
	rm -f $P.debug core core.[0-9]*
	grant_access . $P ${XTRA_INPUTS}
	$M hpcm_sandbox -datasize 1g \
			-space 1g \
		        -stacksize 64m \
		        ${XTRA_LIMITS} \
		        $P debug \
	    <$P.in | tee $P.debug

debug:		$P.debug

submit-%:		test-%
	@if test ! -d ../rubiks-$*; \
	    then echo "\`make submit-$*'" \
	              "is NOT implemented!"; \
	         exit 1; fi
	ln -sf ../rubiks/rubiks.cc \
	       ../rubiks-$*/rubiks-$*.cc
	cd ../rubiks-$*; make submit

clean-%:
	@if cmp -s test-$*.in sample-$*.in; \
	   then echo rm test-$*.in; \
	        rm test-$*.in; fi;
	@if cmp -s test-$*.test sample-$*.test; \
	   then echo rm test-$*.test; \
	        rm test-$*.test; fi; 

clean:	$(TESTS:%=clean-%)
	rm -f $P *.class core core.[0-9]* \
	      *.out *.debug *.fout *.jout *.jfout \
	      make_$P_*input $P.in $P.test

# This is only to be executed by the judge.
#
judges_stuff:
	g++ -g -c rubiks_lib.cc
	g++ -g -o QA -DQA rubiks.cc rubiks_lib.o
