# Makefile for the Right Hand on the Wall Problem
#
# File:		Makefile
# Date:		Sat May  6 01:27:00 EDT 2006
#
# See demonstration Makefile for documentation.
#
# The program for this problem is named:

P = handonwall

.SUFFIXES:
.SUFFIXES: .c .cc .java .lsp

default:	$P.out

.c:
	rm -f $* core core.[0-9]*
	gcc -g -o $* $*.c -lm

.cc:
	rm -f $* core core.[0-9]*
	g++ -g -o $* $*.cc -lm

.java:
	rm -f $* *.class core core.[0-9]*
	javac -g $*.java
	echo >$* '#!/bin/sh'
	echo >>$* "exec `which java` $* \$$*"
	chmod a+r *.class
	chmod a+rx $*

#
.lsp:
	rm -f $* $*.fas $*.lib core core.[0-9]*
	hpcm_clisp -c $*.lsp
	echo >$* '#!/bin/sh'
	echo >>$* \
	    "exec `hpcm_clisp -which` -I $*.fas \$$*"
	chmod a+r $*.fas
	chmod a+rx $*

$P.out:	$P $P.in
	rm -f $P.out core core.[0-9]*
	chmod a+x . $P
	hpcm_sandbox -cputime 60 \
	             -datasize 4m \
		     -stacksize 4m \
		     -filesize 50k \
		     -tee $P.out \
		     $P \
	    <$P.in

$P.debug:	$P $P.in
	rm -f $P.debug core core.[0-9]*
	chmod a+x . $P
	hpcm_sandbox -cputime 60 \
	             -datasize 4m \
		     -stacksize 4m \
		     -filesize 4m \
		     -tee $P.debug \
		     $P debug \
	    <$P.in

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
	      $P.fas $P.lib make_$P_*input

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
#   $Date: 2006/10/04 05:02:27 $
#   $RCSfile: Makefile,v $
#   $Revision: 1.1 $