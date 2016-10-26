// Solution to the Binary Tree Sort Problem
//
// File:	bintreesort.java
// Authors:	Bob Walton (walton@seas.harvard.edu)
// Date:	Mon Apr  7 03:23:24 EDT 2014
//
// The authors have placed this program in the public
// domain; they make no warranty and accept no liability
// for this program.

import java.util.Scanner;
import java.util.TreeMap;
import java.util.NoSuchElementException;
public class bintreesort {

    static boolean debug = false;

    // printf ( format, ... ) prints output using the
    // given format with ... representing the format
    // controlled arguments.
    //
    static void printf
            ( String format, Object ... args )
    {
        System.out.format ( format, args );
    }

    // Ditto but suppress printout if debug == false.
    //
    static void dprintf
            ( String format, Object ... args )
    {
        if ( debug )
	    System.out.format ( format, args );
    }

    // Abort execution with message.
    //
    static void abort ( String message )
    {
	throw new RuntimeException ( message );
    }

    // JAVA TreeMap implements a red-black binary tree.
    // Our dataset is such a tree.  The standard
    // comparison function suffices for comparison of
    // keys, which are `doubles'.  The data associated
    // with a new is not relevant, but must have a type
    // that extends Object, so we use `Object()' data.
    //
    static TreeMap<Double,Object> dataset =
        new TreeMap<Double,Object>();

    // For debugging we keep track of the number of
    // elements in the data set.
    //
    static int setsize = 0;

    // Perform the `A n' operation to add n to the
    // data set.
    //
    static void add ( Double n )
    {
        if ( dataset.get ( n ) != null )
	    dprintf ( "A %.0f failed%n", n );
	else
	{
	    dprintf ( "A %.0f succeeded," +
	              " data set size = %d%n",
		      n, ++ setsize );
	    dataset.put ( n, new Object() );
	}
    }

    // Perform the `R n' operation to remove n from the
    // data set.
    //
    static void remove ( Double n )
    {
        if ( dataset.get ( n ) == null )
	    dprintf ( "R %.0f failed%n", n );
	else
	{
	    dataset.remove ( n );
	    dprintf ( "R %.0f succeeded," +
	              " data set size = %d%n",
		      n, -- setsize );
	}
    }

    // Perform the `P n' operation to print n in the
    // data set.
    //
    static void print ( Double n )
    {
        if ( dataset.get ( n ) == null )
	    printf ( "(%.0f)", n );
	else
	{
	    Double previous =
	        dataset.lowerKey ( n );
	    if ( previous == null )
	        printf ( "(none)" );
	    else
	        printf ("%.0f",
		        previous.doubleValue() );

	    printf (" < %.0f < ", n );

	    Double next =
	        dataset.higherKey ( n );
	    if ( next == null )
	        printf ( "(none)" );
	    else
	        printf ("%.0f", next );
	}
	printf ( "%n" );
    }

    // Perform the `E' operation to empty the data set.
    //
    static void empty ( )
    {
	try {
	    while ( true )
	    {
		Double first = dataset.firstKey();

		dprintf ( "E removes %.0f," +
			  " data set size = %d%n",
			  first, -- setsize );
		dataset.remove ( first );
	    }
	} catch ( NoSuchElementException e ) {}
    }

    public static void main ( String[] args )
    {
	debug = ( args.length > 0 );

	Scanner scan = new Scanner ( System.in );

	while ( scan.hasNextLine() )
	{
	    String name = scan.nextLine();
	    System.out.println ( name );

	    String c = "";
	    while ( ! c.equals ( "E" ) )
	    {
	        c = scan.next();
		switch ( c )
		{
		case "A":
		case "R":
		case "P":
		{
		    Double n =
		        new Double
			    ( scan.nextDouble() );
		    switch ( c )
		    {
		    case "A": add ( n ); break;
		    case "R": remove ( n ); break;
		    case "P": print ( n ); break;
		    }
		    break;
		}
		case "E": empty(); break;
		default:
		    abort ( "ERROR: unrecognized" +
			    " command: " + c );
		}
		name = scan.nextLine();
		if ( ! name.equals ( "" ) )
		    abort ( "ERROR: stuff at end of" +
		            " line: `" + name  + "'");
	    }
	}
    }
}
