# Makefile for the Local Color Problem
#
# File:		Makefile
# Date:		Wed Apr 24 04:41:46 EDT 2013
#
# See demonstration Makefile for documentation.
#
#   P		problem name
#   M		monitor name
#
#   XTRA_INPUTS	extra input files that must be granted
#		access
#   XTRA_LIBS	extra libraries for C and C++ programs
#   XTRA_LIMITS limits that override those given
#               previously to hpcm_sandbox
#   
P = localcolor
M = localcolor_network

XTRA_INPUTS =
XTRA_LIBS =
XTRA_LIMITS =

.SUFFIXES:
.SUFFIXES: .c .cc .java .lsp

default:	$P.out

.c:
	rm -f $* core core.[0-9]*
	gcc -g -o $* $*.c -lm ${XTRA_LIBS}

.cc:
	rm -f $* core core.[0-9]*
	g++ -g -o $* $*.cc -lm ${XTRA_LIBS}

.java:
	rm -f $* *.class core core.[0-9]*
	javac -g $*.java
	echo >$* '#!/bin/sh'
	echo >>$* "exec `which java` -ea $* \$$*"
	chmod a+r *.class
	chmod a+rx $*

#
.lsp:
	rm -f $* core core.[0-9]*
	echo >$* '#!/bin/sh'
	echo >>$* "exec sbcl --script $*.lsp" '"$$@"'
	chmod a+r $*.lsp
	chmod a+rx $*

$P.in:
	if test -r sample.in; \
	then cp sample.in $P.in; chmod u+rw $P.in; fi

$P.test:
	if test -r sample.test; \
	then cp sample.test $P.test; \
	     chmod u+rw $P.test; fi

$P.out:	$P $P.in
	rm -f $P.out core core.[0-9]*
	grant_access . $P ${XTRA_INPUTS}
	$M hpcm_sandbox -cputime 60 \
	                -datasize 64m \
		        -stacksize 16m \
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
	$M hpcm_sandbox -cputime 60 \
	                -datasize 64m \
		        -stacksize 16m \
		        ${XTRA_LIMITS} \
		        $P debug \
	    <$P.in | tee $P.debug

debug:		$P.debug

submit:		$P.out
	hpcm_submit $P

in-submit:	$P.out
	hpcm_submit -in $P

inout-submit:	$P.out
	hpcm_submit -inout $P

solution-submit:	$P.out
	hpcm_submit -solution $P

clean:
	rm -f $P *.class core core.[0-9]* \
	      *.out *.debug *.fout *.jout *.jfout \
	      make_$P_*input
	if cmp -s $P.in sample.in; then rm $P.in; fi
	if cmp -s $P.test sample.test; \
	   then rm $P.test; fi

#
# Note: The monitor program must limit its own cpu time
# and its own i/o sizes (there is no effective hpcm_
# sandbox -filesize argument).

# Derived From:	Makefile2
# Author:	walton@seas.harvard.edu
#
# The authors have placed this file in the public
# domain; they make no warranty and accept no liability
# for this file.
#
# RCS Info (may not be true date or author):
#
#   $Author: walton $
#   $Date: 2013/09/24 20:20:33 $
#   $RCSfile: Makefile,v $
#   $Revision: 1.1 $