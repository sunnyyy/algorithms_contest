// Solution to the Binary Tree Sort Problem
//
// File:	bintreesort.cc
// Authors:	Bob Walton (walton@seas.harvard.edu)
// Date:	Fri Apr  4 03:30:44 EDT 2014
//
// The authors have placed this program in the public
// domain; they make no warranty and accept no liability
// for this program.
//
// RCS Info (may not be true date or author):
//
//   $Author: walton $
//   $Date: 2014/04/04 09:06:40 $
//   $RCSfile: bintreesort.cc,v $
//   $Revision: 1.1 $

#include <iostream>
#include <cstdio>	// sprintf
#include <cstdlib>	// exit, abort
#include <map>		// map
using namespace std;
#include <cstring>	// string
#include <cassert>

bool debug = false;
#define dout    if ( debug ) cout
#define dprintf if ( debug ) printf

/* Avoid definition of `remove' in stdio.h
 */
// #define remove REMOVE


// Numbers must be stored so they may be remembered and
// compared.  A 64-bit IEEE floating point format
// suffices for 15 digit integers.
//
typedef double number;

// A C++ map implements a binary tree.  Our dataset is
// such a tree.  The standard < operator suffices for
// comparison of keys.  The data associated with a key
// is not relevant, so long as there is something, so
// we use the bool value `true'.
//
map<number,bool> dataset;
typedef map<number,bool>::iterator dataset_p;

// For debugging we keep track of the number of elements
// in the data set.
//
int setsize = 0;


// Perform the `A n' operation to add n to the database.
//
void add ( number n )
{
    if ( dataset.count ( n ) != 0 )
    {
	dprintf ( "A %.0f failed\n", (double) n );
    }
    else
    {
	dprintf
	    ( "A %.0f succeeded, data set size = %d\n",
	      (double) n, ++ setsize );
        dataset[n] = true;
    }
}

// Perform the `R n' operation to remove n from the
// database.
//
void remove ( number n )
{
    if ( dataset.count ( n ) )
    {
	dataset.erase ( dataset.find ( n ) );
	dprintf
	    ( "R %.0f succeeded, data set size = %d\n",
	      (double) n, -- setsize );
    }
    else
    {
	dprintf ( "R %.0f failed\n", (double) n );
    }
}

// Perform the `P n' operation to print n in the
// database.
//
void print ( number n )
{
    dataset_p p = dataset.find ( n );
    if ( p == dataset.end() )
        printf ( "(%.0f)", n );
    else
    {
        if ( p == dataset.begin() )
	    printf ( "(none)" );
	else
	{
	    dataset_p q = p;
	    printf ( "%.0f", (double) (--q)->first );
	}
	printf ( " < %.0f < ", n );
	if ( ++ p == dataset.end() )
	    printf ( "(none)" );
	else
	    printf ( "%.0f", (double) p->first );
    }

    cout << endl;
}

// Perform the `E' operation to empty the database.
//
void empty ( void )
{
    dataset_p p = dataset.begin();
    for ( dataset_p p = dataset.begin();
          p != dataset.end();
	  p = dataset.begin() )
    {
	dprintf
	    ( "E removes %.0f, data set size = %d\n",
	      (double) p->first, -- setsize );
	dataset.erase ( p );
    }
}

int main ( int argc, char * argv[] )
{
    debug = ( argc > 1 );

    char name[82];

    while ( cin.getline ( name, sizeof ( name ) ),
            cin.good() )
    {
	assert ( strlen ( name ) <= 81 );
	printf ( "%s\n", name );

	char c = 0;
	while ( c != 'E' )
	{
	    cin >> c;
	    switch ( c )
	    {
	    case 'A':
	    case 'R':
	    case 'P':
	    {
	        number n;
		cin >> n;
		switch ( c )
		{
		case 'A': add ( n ); break;
		case 'R': remove ( n ); break;
		case 'P': print ( n ); break;
		}
		break;
	    }
	    case 'E': empty(); break;
	    default:
	        assert ( ! "recognized command" );
	    }
	    cin.getline ( name, sizeof ( name ) );
	    assert ( name[0] == 0 );
	}
    }

    return 0;
}
