# Solution to the Word Order Reverser Problem
#
# File:		reverser.py
# Authors:	Bob Walton (walton@seas.harvard.edu)
# Date:		Wed Sep 28 06:32:44 EDT 2016
#
# The authors have placed this program in the public
# domain; they make no warranty and accept no liability
# for this program.

# reverser [-pattern] [debug]
#
# Without the -pattern option this program just uses
# hand coded scanning.  With -pattern the program uses
# regular expressions.

import sys
import re

debug = False
use_pattern = False
for arg in sys.argv[1:]:
    if arg == "-pattern":
        use_pattern = True
    else:
        debug = True

def dprint (*args):
    global debug
    if debug:
        for arg in args:
	    print arg,
	print

def read():
    try:
        result = raw_input().rstrip ( '\n' )
    except EOFError:
        result = None
    finally:
        return result


pattern = r'[^a-z]+|[a-z]+'
regexp = re.compile ( pattern )

while True:

    line = read()
    if line == None:
        break

    # Decompose the line into a list of substrings
    # that alternate between words and separators.
    # The first and last are separators, and may
    # be empty, but all other substrings must have
    # at least 1 character.

    if use_pattern:
	items = re.findall ( regexp, line )
	if len ( items ) == 0:
	    items.append ( '' )
	else:
	    if items[0].isalpha():
	        items = [''] + items
	    if items[-1].isalpha():
	        items = items + ['']
    else:
	items = []
	next = ''
	mode = 'separator'
	for c in line:
	    if mode == 'separator':
	        if not c.isalpha():
		    next += c
		else:
		    items.append ( next )
		    next = c
		    mode = 'word'
	    else:
	        if c.isalpha():
		    next += c
		else:
		    items.append ( next )
		    next = c
		    mode = 'separator'

	items.append ( next )
	if mode == 'word':
	    items.append ( '' )
	    
    dprint ( items )

    # Reverse words in items.
    #
    i = 1
    j = len ( items ) - 2
    while i < j:
	tmp = items[i]
	items[i] = items[j]
	items[j] = tmp
	i += 2
	j -= 2

    # Output items as a line.
    #
    for item in items:
	sys.stdout.write ( item )
    print
