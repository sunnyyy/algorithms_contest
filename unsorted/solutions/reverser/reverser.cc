// Solution to the Word Order Reverser Problem
//
// File:	reverser.cc
// Authors:	Bob Walton (walton@seas.harvard.edu)
// Date:	Thu Jan 24 03:26:32 EST 2013
//
// The authors have placed this program in the public
// domain; they make no warranty and accept no liability
// for this program.
//
// RCS Info (may not be true date or author):
//
//   $Author: walton $
//   $Date: 2013/01/24 08:26:43 $
//   $RCSfile: reverser.cc,v $
//   $Revision: 1.7 $

#include <iostream>
#include <cstdio>
using namespace std;
#include <cctype>
#include <cassert>

int debug = false;
#define dout    if ( debug ) cout
#define dprintf if ( debug ) printf

char line[81];

// Function to find and print the first word BEFORE q,
// where q points into `line'.  It is a program error
// if there is no such word.  Returns pointer to the
// first character of the word printed.
//
char * print_substitute_word ( char * q )
{
    // Move q backward to point just after word.
    //
    while ( 1 )
    {
        assert ( q > line );
	if ( isalpha ( q[-1] ) ) break;
	-- q;
    }
    char * p = q;  // p points just after word.

    // Move q to point at 1st character of word.
    //
    -- q;
    while ( q > line && isalpha ( q[-1] ) ) -- q;

    // Print word and return.
    //
    char save = * p;
    * p = 0;
    cout << q;
    * p = save;
    return q;
}

int main ( int argc, char * argv[] )
{
    debug = ( argc > 1 );

    while ( cin.getline ( line, sizeof ( line ) ),
            cin.good() )
    {
	// When debugging print the intput as well as
	// the output.
	//
	dout << line << endl;

    	// Set p to beginning of line and q to end of
	// line.
	//
	char * p = line, * q = line;
	while ( * q ) ++ q;

	// Print line substituting for words.
	//
	while ( * p )
	{
	    if ( isalpha ( * p ) )
	    {
		// At start of word. Skip word.
		//
	        while ( isalpha ( * p ) ) ++ p;

		// Substitute for skipped word.
		//
		q = print_substitute_word ( q );
	    }
	    else
	    {
	        // Print and skip non-letter.
		//
	        cout << * p ++;
	    }
	}
	cout << endl;
    }

    return 0;
}
