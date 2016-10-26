/* Solution to the Binary Tree Sort Problem
 *
 * File:	bintreesort.c
 * Authors:	Bob Walton (walton@seas.harvard.edu)
 * Date:	Wed Apr  2 20:55:14 EDT 2014
 *
 * The authors have placed this program in the public
 * domain; they make no warranty and accept no liability
 * for this program.
 *
 * RCS Info (may not be true date or author):
 *
 *   $Author: walton $
 *   $Date: 2014/04/03 11:17:19 $
 *   $RCSfile: bintreesort.c,v $
 *   $Revision: 1.4 $
 */

#include <stdio.h>	/* sprintf */
#include <stdlib.h>	/* malloc, free */
#include <string.h>	/* strlen */
#include <search.h>	/* tsearch, tfind, tdelete */
#include <assert.h>

/* Avoid definition of `remove' in stdio.h
 */
#define remove REMOVE


int debug = 0;
#define dprintf if ( debug ) printf

/* Numbers must be stored so they may be remembered and
 * compared.  A 64-bit IEEE floating point format
 * suffices for 15 digit integers.
 */
typedef double number;

/* search.h implements a tree of nodes, which are
 * structures, with the first thing in the node being
 * a pointer to a user defined item, which contains
 * the key.  The tree proper is a variable pointing
 * at the root of the tree, or equal to NULL for an
 * empty tree.  Our dataset is such a tree.
 */
typedef void node;
node * dataset;

/* The item type contains the number, which acts as the
 * key, and pointers for a doubly linked list that
 * contains all items in number sorted order, with a
 * special item, the `head', as both the beginning and
 * end of the list (the head is not part of the
 * dataset).
 */
typedef struct item_struct {
    number key;
    struct item_struct * previous;
    struct item_struct * next;
} item;
item head;

/* For debugging we keep track of the number of elements
 * in the data set.
 */
int setsize = 0;

/* Get the item pointed at by a node.
 */
inline item * item_of ( const node * n )
{
    return * (item **) n;
}

/* Compare two items.
 */
int compare ( const void * xp, const void * yp )
{
    number x = ( (const item *) xp ) -> key;
    number y = ( (const item *) yp ) -> key;
    return x < y ? -1 : x == y ? 0 : +1;
}

/* Perform the `A n' operation to add n to the database.
 */
void add ( number n )
{
    node * parent = dataset;

    item * new_item =
        (item *) malloc ( sizeof ( item ) );
    new_item->key = n;
    node * found_node =
        tsearch ( new_item, & dataset, compare );
    if ( item_of ( found_node ) != new_item )
    {
        free ( new_item );
	dprintf ( "A %.0f failed\n", (double) n );
	return;
    }

    if ( parent == NULL )
    {
        /* Item is first in dataset.  Add it to list
	 * and return.
	 */

	new_item->previous = new_item->next = & head;
	head.previous = head.next = new_item;
	dprintf
	    ( "A %.0f is first, data set size = %d\n",
	      (double) n, ++ setsize );
	return;
    }
    else if ( item_of ( parent ) != new_item )
    {
        /* New item is not now at root of tree.  Find
	 * its parent by removing item and then
	 * reinserting it.
	 */
	parent = (node *)
	    tdelete ( new_item, & dataset, compare );
	tsearch ( new_item, & dataset, compare );
    }
    else
    {
        /* New item is root of tree and not only
	 * thing in the tree.  Pretend old tree
	 * root is parent.
	 */
    }

    assert ( parent != NULL );
    item * pitem = item_of ( parent );
    if ( pitem->key > new_item->key )
    {
        /* pitem->key > n: move pitem down list until
	 * it is the smallest with this property and
	 * insert new_item before this pitem.
	 */
        while ( 1 )
	{
	    item * previous = pitem->previous;
	    if ( previous == & head ) break;
	    if ( previous->key < new_item->key )
	        break;
	    pitem  = previous;
	}
	new_item->next = pitem;
	new_item->previous = pitem->previous;
	new_item->next->previous = new_item;
	new_item->previous->next = new_item;
	dprintf
	    ( "A %.0f before %.0f,"
	      " data set size = %d\n",
	      (double) n, (double) pitem->key,
	      ++ setsize );
    }
    else
    {
        /* pitem->key < n: move pitem down list until
	 * it is the largest with this property and
	 * insert new_item after this pitem.
	 */
	assert ( pitem->key < new_item->key );
        while ( 1 )
	{
	    item * next = pitem->next;
	    if ( next == & head ) break;
	    if ( next->key > new_item->key )
	        break;
	    pitem  = next;
	}
	new_item->previous = pitem;
	new_item->next = pitem->next;
	new_item->next->previous = new_item;
	new_item->previous->next = new_item;
	dprintf
	    ( "A %.0f after %.0f, data set size = %d\n",
	      (double) n, (double) pitem->key,
	      ++ setsize );
    }
}

/* Perform the `R n' operation to remove n from the
 * database.
 */
void remove ( number n )
{
    item i;
    i.key = n;
    node * found_node =
        tfind ( & i, & dataset, compare );
    if ( found_node != NULL )
    {
	item * fitem = item_of ( found_node );
	tdelete ( fitem, & dataset, compare );
	fitem->next->previous = fitem->previous;
	fitem->previous->next = fitem->next;
        free ( fitem );
	dprintf
	    ( "R %.0f succeeded, data set size = %d\n",
	      (double) n, -- setsize );
    } else
	dprintf ( "R %.0f failed\n", (double) n );
}

/* Perform the `P n' operation to print n in the
 * database.
 */
void print ( number n )
{
    item i;
    i.key = n;
    node * found_node =
        tfind ( & i, & dataset, compare );
    if ( found_node == NULL )
        printf ( "(%.0f)\n", n );
    else
    {
        item * fitem = item_of ( found_node );
	if ( fitem->previous == & head )
	    printf ( "(none)" );
	else
	    printf ( "%.0f", fitem->previous->key );
	printf ( " < %.0f < ", n );
	if ( fitem->next == & head )
	    printf ( "(none)\n" );
	else
	    printf ( "%.0f\n", fitem->next->key );
    }
}

/* Perform the `E' operation to empty the database.
 */
void empty ( void )
{
    item * ditem = head.next;
    while ( ditem != & head )
    {
	dprintf
	    ( "E removes %.0f, data set size = %d\n",
	      (double) ditem->key, -- setsize );
        tdelete ( ditem, & dataset, compare );
	item * next = ditem->next;
	free ( ditem );
	ditem = next;
    }

    assert ( dataset == NULL );

    head.next = & head;
    head.previous = & head;
}

int main ( int argc, char * argv[] )
{
    debug = ( argc > 1 );

    head.previous = & head;
    head.next = & head;
    dataset = NULL;

    char name[83];

    while ( fgets ( name, sizeof ( name ), stdin ) )
    {
	assert ( strlen ( name ) <= 81 );
	printf ( "%s", name );

	char c = 0;
	while ( c != 'E' )
	{
	    scanf ( "%c", & c );
	    switch ( c )
	    {
	    case 'A':
	    case 'R':
	    case 'P':
	    {
	        number n;
		scanf ( "%lf", & n );
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
	    fgets ( name, sizeof ( name ), stdin );
	    assert ( name[0] == '\n' );
	}
    }

    return 0;
}
