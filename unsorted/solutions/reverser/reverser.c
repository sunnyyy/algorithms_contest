/* Solution to the Word Order Reverser Problem
 *
 * File:	reverser.c
 * Authors:	Bob Walton (walton@seas.harvard.edu)
 * Date:	Mon Mar 31 03:08:17 EDT 2014
 *
 * The authors have placed this program in the public
 * domain; they make no warranty and accept no liability
 * for this program.
 *
 * RCS Info (may not be true date or author):
 *
 *   $Author: walton $
 *   $Date: 2014/03/31 07:09:21 $
 *   $RCSfile: reverser.c,v $
 *   $Revision: 1.8 $
 */


#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

int debug = 0;
#define dprintf if ( debug ) printf

char line[82];

/* Function to find and print the first word BEFORE q,
 * where q points into `line'.  It is a program error
 * if there is no such word.  Returns pointer to the
 * first character of the word printed.
 */
char * print_substitute_word ( char * q )
{
    char * p, save;

    /* Move q backward to point just after word.
     */
    while ( 1 )
    {
        assert ( q > line );
	if ( isalpha ( q[-1] ) ) break;
	-- q;
    }
    p = q;  /* p points just after word. */

    /* Move q to point at 1st character of word.
     */
    -- q;
    while ( q > line && isalpha ( q[-1] ) ) -- q;

    /* Print word and return.
     */
    save = * p;
    * p = 0;
    printf ( "%s", q );
    * p = save;
    return q;
}

int main ( int argc, char * argv[] )
{
    debug = ( argc > 1 );

    while ( fgets ( line, sizeof ( line ), stdin ) )
    {
	char * p, * q;

	/* When debugging print the input as well as
	 * the output.
	 */
	dprintf ( "%s", line );

    	/* Set p to beginning of line and q to end of
	 * line.
	 */
	p = line, q = line;
	while ( * q ) ++ q;

	/* Print line substituting for words.
	 */
	while ( * p )
	{
	    if ( isalpha ( * p ) )
	    {
		/* At start of word. Skip word.
		 */
	        while ( isalpha ( * p ) ) ++ p;

		/* Substitute for skipped word.
		 */
		q = print_substitute_word ( q );
	    }
	    else
	    {
	        /* Print and skip non-letter.
		 */
	        printf ( "%c", * p ++ );
	    }
	}
    }

    return 0;
}
