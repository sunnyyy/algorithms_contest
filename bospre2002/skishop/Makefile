# Makefile for the Ski Shop Problem
#
# File:		Makefile
# Date:		Sun Feb 17 08:27:21 EST 2002
#
# See demonstration Makefile for documentation.
#
# The program for this problem is named:

P = skishop

.SUFFIXES:
.SUFFIXES: .c .cc .java .p .lsp

default:	$P.out

.c:
	rm -f $* core
	gcc -g -o $* $*.c -lm

.cc:
	rm -f $* core
	g++ -g -o $* $*.cc -lm

.p:
	rm -f $* $*.p2c core
	p2c -o $*.p2c $*.p
	gcc -g -o $* -x c $*.p2c -lp2c -lm

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

clean:
	rm -f $P *.class $P.p2c core $P.out \
	      $P.fas $P.lib


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
#   $Date: 2002/10/09 05:19:38 $
#   $RCSfile: Makefile,v $
#   $Revision: 1.1 $