// Solution to the Word Order Reverser Problem
//
// File:	reverser.java
// Authors:	Bob Walton (walton@seas.harvard.edu)
// Date:	Mon Jan  7 19:00:53 EST 2013
//
// The authors have placed this program in the public
// domain; they make no warranty and accept no liability
// for this program.

// reverser [-pattern] [debug]
//
// Without the -pattern option this program just uses
// hand coded scanning.  With -pattern the program uses
// Patterns with the Scanner.

import java.util.Scanner;
import java.util.regex.Pattern;
public class reverser {

    static boolean debug = false;
    static boolean use_pattern = false;

    final static int MAX_LINE = 80;

    public static void main ( String[] args )
    {
	if ( args.length > 0
	     &&
	     args[0].equals ( "-pattern" ) )
	{
	    use_pattern = true;
	    debug = ( args.length > 1 );
	}
	else
	    debug = ( args.length > 0 );

	Scanner scan = new Scanner ( System.in );

	// Decompose a line into a list of n substrings
	// that alternate between words and separators.
	// The first and last are separators, and may
	// be empty, but all other substrings must have
	// at least 1 character.

	Pattern word =
	    Pattern.compile ( "\\G[a-z]+" );
	Pattern separator =
	    Pattern.compile ( "\\G[^a-z]*" );
	    // \G anchors the pattern at the beginning
	    // of the remaining text.  Otherwise using
	    // a pattern may skip text that is not part
	    // of the pattern.

	String substring[] = new String[MAX_LINE+2];

	while ( scan.hasNextLine() )
	{
	    int n = 0;
	        // Number of substrings in line.

	    if ( use_pattern )
	    {
		while ( true )
		{
		    String item;

		    // Read separator.  If the separator
		    // is an empty String, null is
		    // returned instead of "".
		    //
		    item =
		        scan.findInLine ( separator );
		    if ( item == null ) item = "";
		    substring[n++] = item;

		    // Read word.  If there is none,
		    // null is returned.
		    //
		    item = scan.findInLine ( word );
		    if ( item == null ) break;
		    substring[n++] = item;
		}

		// Skip line feed at end of line.
		//
		scan.nextLine();
	    }
	    else
	    {
		// Read line and scan through it using
		// index i.
		//
	        String line = scan.nextLine();
		int i = 0;
		while ( true )
		{

		    // Skip past non-letters, and
		    // collect characters skipped into
		    // a separator.
		    //
		    int j = i;
		    while ( i < line.length()
		            &&
			    ! Character.isLetter
			        ( line.charAt ( i ) ) )
		        ++ i;
		    substring[n++] =
		        line.substring ( j, i );

		    // If we are at line end, stop.
		    //
		    if ( i == line.length() )
		        break;

		    // Skip past letters, and collect
		    // characters skipped into a word.
		    //
		    j = i;
		    while ( i < line.length()
		            &&
			    Character.isLetter
			        ( line.charAt ( i ) ) )
		        ++ i;
		    substring[n++] =
		        line.substring ( j, i );
		}
	    }

	    if ( debug )
	    {
	        // Print contents of substrings list
		// with elements separated by |'s.
		//
	        System.out.print ( "UNREVERSED: " );
		for ( int i = 0; i < n; ++ i )
		    System.out.print
		        ( "|" + substring[i] );
		System.out.println ( "|" );
	    }

	    // Reverse words in substrings.
	    //
	    int i = 1;
	    int j = n - 2;
	    while ( i < j )
	    {
		String tmp = substring[i];
		substring[i] = substring[j];
		substring[j] = tmp;
		i += 2;
		j -= 2;
	    }

	    // Output substrings as a line.
	    //
	    for ( i = 0; i < n; ++ i )
		System.out.print ( substring[i] );
	    System.out.println();
	}

    }
}
