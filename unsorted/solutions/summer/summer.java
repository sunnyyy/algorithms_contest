// Solution to the Summation Checking Problem
//
// File:	summer.java
// Authors:	Bob Walton (walton@seas.harvard.edu)
// Date:	Tue Jan  8 08:05:06 EST 2013
//
// The authors have placed this program in the public
// domain; they make no warranty and accept no liability
// for this program.

import java.util.Scanner;
public class summer {

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

    public static void main ( String[] args )
    {
	debug = ( args.length > 0 );

	Scanner scan = new Scanner ( System.in );

	while ( scan.hasNextLine() )
	{
	    String casename = scan.nextLine();
	    System.out.println ( casename );

	    // As long as there are numbers in the
	    // input, read these numbers and compute
	    // their sum.  Note we assume each number
	    // ends just before whitespace.
	    //
	    double corrected_sum = 0;
	    while ( scan.hasNextDouble() )
	        corrected_sum += scan.nextDouble();

	    // Read and check =-sign, which must be
	    // surrounded by whitespace.
	    //
	    assert ( scan.next().equals ( "=" ) );

	    // Read accountant computed sum and the
	    // end of line which follows it.
	    //
	    double sum  = scan.nextDouble();
	    scan.nextLine();

	    // If debugging, look at corrected_sum and
	    // sum at maximum precision.
	    //
	    dprintf
	      ( "SUM = %.16f, CORRECTED SUM = %.16f%n",
		sum, corrected_sum );

	    // Print output.  Errors less than 0.005
	    // must be due to internal rounding and not
	    // to the accountants.
	    //
	    if (   Math.abs ( sum - corrected_sum )
	         < 0.005 )
		printf ( "%.2f is correct%n", sum );
	    else
		printf ( "%.2f should be %.2f%n",
			 sum, corrected_sum );
	    }
    }
}
