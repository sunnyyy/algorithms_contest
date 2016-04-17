// Rubik's Cube Library Header File
//
// File:	rubiks.h
// Authors:	Bob Walton (walton@seas.harvard.edu)
// Date:        Tue Feb 23 03:59:21 EST 2016
//
// The authors have placed this program in the public
// domain; they make no warranty and accept no liability
// for this program.

// Table of Contents:
//
// 	Setup
//	System
//	Input
//	Cube Symmetries
//	Cubelets and Their Names
// 	Positions
//	States
// 	Faces

// Setup
// -----

// WARNING: This is a C language file.
//          To include in a C++ file, you must:
//
// 	extern "C" {
// 	# include "rubiks.h"
// 	}
//
// WARNING: C language files must be compiled using:
//
//		gcc -O2 -o rubiks -std=c99 \
//		        rubiks-io.c rubiks_lib.o \
//		        -lstdc++
//
//	    -O2 is needed else `inline's are ignored
//	    -std=c99 is needed for `inline's
//	                       and FOR macro
//	    -lstdc++ is needed by rubiks_lib.o

// `init() must be called at the beginning of your
// `main' function.
//
void init_color_symmetry ( void );
void init_position ( void );
inline void init ( void )
{
    init_color_symmetry();
    init_position();
}

# include <string.h>
# include <math.h>
# define BOOL int
# define TRUE 1
# define FALSE 0

# define MAX_LINE 80
# define EDGE_CUBELETS 12
# define CORNER_CUBELETS 8
# define CUBELETS ( EDGE_CUBELETS + CORNER_CUBELETS )
# define CUBELET_NAME_SIZE 4
	    // Includes NUL.
# define POSITIONS 24
# define ROTATIONS 18
# define MAX_Nr 6

# define MISSING -1
    // Has missing value (i.e., no value).
    // WARNING: Do NOT set this to 0.
# define MULTIPLE -2
    // Has multiple (but unspecified) values.

// Return true if a value that should be >= 0 is instead
// MISSING or MULTIPLE.
//
inline BOOL is_illegal ( int i )
{
    return i < 0;
}

# define FOR(i,n) for ( int i = 0; i < (n); ++ i )


// System
// ------

// Output line of form `** ERROR: <message>' and exit(1)
// if input is not a tty, or return if input is a tty.
//
void error ( const char * message );

// Return if input is a tty; otherwise exit(1).
//
void error_exit ( void );

// Return the CPU seconds used by the current process so
// far.
//
double cpu_time ( void );


// Input
// -----

// Read line (into the `line' global string).  Skip over
// lines beginning with `--' or `**' and blank lines.
//
// If line is too long (longer than MAX_LINE) or ends
// with an end of file and not a line feed, output error
// message, and then skip line if input is from a
// terminal, or exit if input is not from a terminal.
//
// Exit program on an end of file.
//
// Echo lines read if lines are read from a regular
// file (but not if from a terminal or pipe, such as
// the pipe from QA).
//
// Initialize lexeme scanner (see below) when a line is
// read.
//
extern char line[MAX_LINE+2];
void read_line ( void );

// Return the next lexeme in a line, and skip over that
// lexeme.
//
// NULL is returned if there is no next lexeme.
//
const char * next_lexeme ( void );

// Ditto but do not skip over lexeme.
//
const char * next_lexeme_peek ( void );

// Backup over the last lexeme in the line that was
// skipped, and return that lexeme.  Return NULL if
// there is no such lexeme.
//
const char * previous_lexeme ( void );

// If the next lexeme equals s, skip it and return TRUE.
// Else return FALSE and do not skip the lexeme.
//
BOOL is_word ( const char * s );

// If the next lexeme is a number, skip it and return
// the value of the number.  Else return NAN (defined in
// math.h) and do not skip the lexeme.
//
double is_number ( void );

// Check that number is an integer.
//
inline BOOL is_integer ( double d )
{
    return (long long) d == d;
}

// If there are no more lexemes in the last line read,
// return TRUE.  Else return FALSE.
//
BOOL at_end ( void );

// Cube Symmetries
// ---- ----------

// We use the fact that the following color permutations
// preserve Rubik's Cube orientation and therefore
// generate symmetries of the set of face edges, the set
// of corner edges, and the set of rotations.
//
//     0: R --> B --> O --> G --> R
//     1: R --> W --> O --> Y --> R
//     2: B --> W --> G --> Y --> B
//
// color_symmetry[i][c] is the color that symmetry i (0,
// 1, or 2 above) maps c onto.
//
extern char color_symmetry[3][128];
    //
    // color_symmetry[0]['R'] = 'B';
    // color_symmetry[0]['B'] = 'O';
    // color_symmetry[0]['O'] = 'G';
    // color_symmetry[0]['G'] = 'R';
    //
    // color_symmetry[1]['R'] = 'W';
    // color_symmetry[1]['W'] = 'O';
    // color_symmetry[1]['O'] = 'Y';
    // color_symmetry[1]['Y'] = 'R';
    //
    // color_symmetry[2]['B'] = 'W';
    // color_symmetry[2]['W'] = 'G';
    // color_symmetry[2]['G'] = 'Y';
    // color_symmetry[2]['Y'] = 'B';
    //
    // color_symmetry[i][c] = c for all other i and c.
 
// Apply the color symmetry with index i to the string
// s of ASCII characters.  Note that characters that are
// not color names (W, G, R, B, O, or Y) are not
// changed.
//
inline void apply_symmetry ( char * s, int i )
{
    int length = strlen ( s );
    FOR ( j, length )
        s[j] = color_symmetry[i][s[j]];
}


// Cubelets and Their Names
// -------- --- ----- -----

// Cubelet name.
//
typedef char name[CUBELET_NAME_SIZE];

// Rotate in place a string right to left one character.
//
inline void rotate ( char * n )
{
    int length = strlen ( n );
    char first = n[0];
    memmove ( n, n+1, length - 1 );
    n[length-1] = first;
}

// Return true iff a n is canonical, that is, if the
// first character of n is the alphabetically least
// character of n.
//
inline BOOL is_canonical ( const name n )
{
    return ( n[0] < n[1]
             &&
	     ( n[2] == 0
	       ||
	       n[0] < n[2] ) );
}

// Rotate a name n1 until it is canonical.
//
inline void canonicalize ( name n1 )
{
    while ( ! is_canonical ( n1 ) )
        rotate ( n1 );
}

// Rotate a name n1 until it is canonical, and rotate
// n2 by the same amount.
//
inline void canonicalize2 ( name n1, name n2 )
{
    while ( ! is_canonical ( n1 ) )
    {
        rotate ( n1 );
	rotate ( n2 );
    }
}
    

// cubelet[i] is the (canonical) name of the cubelet
// with index i.  Edge cubelets are first, and then
// corner cubelets.
//
extern name cubelet[CUBELETS];
    // = { "BR", "RW", "GR", "RY",
    //     "BO", "OW", "OY", "GO",
    //     "BW", "GW", "GY", "BY",
    //     "BRW", "GWR", "GRY", "BYR",
    //     "BWO", "GOW", "GYO", "BOY" };

// Return index of cubelet given name, or MISSING if no
// cubelet with given name.  If name is not canonical,
// MISSING will be returned.
//
inline int find_cubelet ( const name n )
{
    FOR ( i, CUBELETS )
    {
        if ( strcmp ( cubelet[i], n ) == 0 )
	    return i;
    }
    return MISSING;
}

// Positions
// ---------

// position[i][j] is the name n2 such that if n1 =
// cubelet[i] then n1/n2 is the given position.
//
// E.g., if cublet[i] == "BR" and position[i][j] = "RG"
// then position j of cubelet i is BR/RG.
//
extern name position[CUBELETS][POSITIONS];

// Given i return j such that position[i][j] == n,
// or return MISSING if none.
//
inline int find_position ( int i, const name n )
{
    FOR ( j, POSITIONS )
    {
        if ( strcmp ( position[i][j], n ) == 0 )
	    return j;
    }
    return MISSING;
}

// Print the position matrix for debugging purposes.
// I.e., print  cublet[i]/position[i][j] for all
// i and j.
//
void print_position ( void );

// States
// ------

// A state s has a position s[i] for every cubelet[i].
// More explicitly, the position name is
// cubelet[i] / position[i][s[i]].  s[i] may also be
// MISSING or MULTIPLE.
// 
typedef char state[CUBELETS];

// Given a position n1/n2, first canonicalize it, and
// then set the appropriate state s element to record
// that position, unless that state element is already
// set to MULTIPLE or has a different non-MISSING value.
// If the element is already MULTIPLE, do nothing.  If
// it has a different non-MISSING value, set the value
// to MULTIPLE.
//
// Return true if at the end the element is not MULTIPLE
// and false otherwise.
//
// Also, if n1 canonicalized does not name a cubelet,
// or if n1/n2 does  not name a position, return false
// and do nothing.  Note this will happen if n1 or n2
// contain characters equal to MISSING or MULTIPLE
// (because they were composed from an exploded view
// some of whose characters were MISSING or MULTIPLE).
//
inline BOOL set_state_position
	( state s, name n1, name n2 )
{
    canonicalize2 ( n1, n2 );
    int i = find_cubelet ( n1 );
    if ( i == MISSING ) return FALSE;
    int j = find_position ( i, n2 );
    if ( j == MISSING ) return FALSE;

    if ( s[i] == MISSING )
	{ s[i] = j; return TRUE; }
    else if ( s[i] == MULTIPLE ) return FALSE;
    else if ( s[i] != j )
	{ s[i] = MULTIPLE; return FALSE; }
    else return TRUE;
}

// Set a state to the solved state.
//
inline void set_state_solved ( state s )
{
    FOR ( i, CUBELETS )
        s[i] = find_position ( i, cubelet[i] );
}

// Faces
// -----
    
// A face is a 3x3 matrix of colors, with the center
// color being the face `name'.  An exploded_view is
// 6 faces, one for each color.  For face f, f[0][0]
// is the lower left color in the exploded view.
//
// face[i][j] for i != 0 or j != 0 may be MISSING
// or MULTIPLE.  For example, if the face is generated
// from a state, either zero or more than one cubelet
// may be mapped to a particular face element.
//
typedef char face[3][3];
typedef struct exploded_view
{
    face f[128];
        // Faces are f['W'], f['G'], f['R'],
	//           f['B'], f['O'], f['Y'];
	// We do not need to conserve memory here
	// and so waste 128 - 6 faces of memory.
} exploded_view;

// Write an exploded view in 9 lines.  Output MISSING
// and MULTIPLE elements as `*'.
//
void write_exploded_view ( const exploded_view * vp );

// Read an exploded view of 9 lines.  It is an error
// unless the input is correctly formatted and has
// only upper case letters or `*' for face elements.
// Input from QA may be assumed to be error free
// in this sense.
//
// `*'s in the input are changed to MISSING values in
// the exploded view faces.
//
// On an error, an error message is printed and
// error_exit() is called.
//
void read_exploded_view ( exploded_view * vp );

// Check exploded view to see if center colors are
// correct.  Return true if yes.  Otherwise set
// incorrect center colors to MISSING and return false.
//
inline BOOL check_exploded_view ( exploded_view * vp )
{
    BOOL result = TRUE;
    if ( vp->f['W'][1][1] != 'W' )
        vp->f['W'][1][1] = MISSING, result = FALSE;
    if ( vp->f['G'][1][1] != 'G' )
        vp->f['G'][1][1] = MISSING, result = FALSE;
    if ( vp->f['R'][1][1] != 'R' )
        vp->f['R'][1][1] = MISSING, result = FALSE;
    if ( vp->f['B'][1][1] != 'B' )
        vp->f['B'][1][1] = MISSING, result = FALSE;
    if ( vp->f['O'][1][1] != 'O' )
        vp->f['O'][1][1] = MISSING, result = FALSE;
    if ( vp->f['Y'][1][1] != 'Y' )
        vp->f['Y'][1][1] = MISSING, result = FALSE;
    return result;
}

// Set an exploded view into solved position.
//
void set_exploded_view_solved ( exploded_view * vp );

// Convert exploded_view to state.  Return false if any
// state position is set to MISSING or MULTIPLE, but
// return true otherwise.
//
// MISSING or MULTIPLE face elements in the exploded
// view are ignored, and by the Pigeon Hole Principal
// cause MISSING state elements.
//
BOOL convert_to_state
    ( state s, const exploded_view * vp );

// Convert state to exploded_view.  Return false if any
// face element is set to MISSING or MULTIPLE, but
// return true otherwise.
//
// MISSING or MULTIPLE state elements are ignored, and
// by the Pigeon Hole Principal cause MISSING face
// elements in the exploded view.
//
BOOL convert_to_exploded_view
    ( exploded_view * vp, const state s );
