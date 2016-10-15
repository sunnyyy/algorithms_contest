# Makefile for the Fair Eye's Secret Problem
#
# File:		Makefile
# Date:		Wed Oct  5 06:48:16 EDT 2005
#
# See demonstration Makefile for documentation.
#
# The program for this problem is named:

P = faireye

.SUFFIXES:
.SUFFIXES: .c .cc .java .lsp

default:	$P.out

.c:
	rm -f $* core
	gcc -g -o $* $*.c -lm

.cc:
	rm -f $* core
	g++ -g -o $* $*.cc -lm

.java:
	rm -f $* *.class core
	javac -g $*.java
	echo >$* '#!/bin/sh'
	echo >>$* "exec `which java` $*"
	chmod a+r *.class
	chmod a+rx $*

#
.lsp:
	rm -f $* $*.fas $*.lib core
	hpcm_clisp -c $*.lsp
	echo >$* '#!/bin/sh'
	echo >>$* "exec `hpcm_clisp -which` -I $*.fas"
	chmod a+r $*.fas
	chmod a+rx $*

$P.out:	$P $P.in
	rm -f $P.out core
	chmod a+x . $P
	hpcm_sandbox -cputime 60 \
	             -datasize 4m \
		     -stacksize 4m \
		     -filesize 50k \
		     -watch \
		     $P \
	    <$P.in >$P.out
	@echo ""
	@echo "========== OUTPUT ($P.out)" \
	      "=========="
	@cat $P.out
	@echo "============== END OUTPUT =============="

submit:		$P.out
	hpcm_submit $P

in-submit:	$P.out
	hpcm_submit -in $P

inout-submit:	$P.out
	hpcm_submit -inout $P

solution-submit:	$P.out
	hpcm_submit -solution $P

clean:
	rm -f $P *.class core $P.out $P.fout $P.jout \
	      $P.jfout $P.fas $P.lib make_$P_input

#
# Author:	walton@deas.harvard.edu
#
# The authors have placed this file in the public
# domain; they make no warranty and accept no liability
# for this file.
#
# RCS Info (may not be true date or author):
#
#   $Author: walton $
#   $Date: 2005/10/16 12:19:16 $
#   $RCSfile: Makefile,v $
#   $Revision: 1.1 $