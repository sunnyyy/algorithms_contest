/* Solution to the Simple Vector Calculator Problem
 *
 * File:	vcalc.c
 * Authors:	Bob Walton (walton@seas.harvard.edu)
 * Date:	Mon Feb 11 05:02:25 EST 2013
 *
 * The authors have placed this program in the public
 * domain; they make no warranty and accept no liability
 * for this program.
 *
 * RCS Info (may not be true date or author):
 *
 *   $Author: walton $
 *   $Date: 2013/02/11 10:03:31 $
 *   $RCSfile: vcalc.c,v $
 *   $Revision: 1.3 $
 */

#include <stdio.h>	/* sprintf */
#include <stdlib.h>	/* exit, abort */
#include <stdarg.h>	/* va_list */
#include <string.h>	/* string */
#include <assert.h>
#include <ctype.h>	/* isspace, isblank */
#include <math.h>	/* fabs, atan2, sqrt, M_PI */

int debug = 0;
#define dprintf if ( debug ) printf

/* Strings are NUL terminated char *'s allocated by
 * malloc, reallocated by realloc, and freed by free.
 */
typedef const char * string;

/* Shorthand of equality of strings.
 */
int eq ( string x, string y )
{
    return strcmp ( x, y ) == 0;
}

/* Convert double to string.  Use %.14f and strip
 * trailing 0's and if integer also the `.'.
 */
string to_string ( double d )
{
    char buffer[100];
    char * p = buffer + sprintf ( buffer, "%.14f", d );
    while ( p[-1] == '0' ) -- p;
    if ( p[-1] == '.' ) -- p;
    * p = 0;
    return strdup ( buffer );
}

/* Convert string to double.  Return true on success
 * and false on failure.  Assumes string is not
 * empty.
 */
int to_number ( string s, double * result )
{
    char * q;
    * result = strtod ( s, & q );
    return * q == 0;
}

/* Skip input until next non-whitespace or end of line
 * or end of file if `comment' is false, or until next
 * end of line or end of file if `comment' is true.
 * Return next non-whitespace character (which is not
 * skipped), or '\n' for end of line (the line feed IS
 * skipped), or EOF for end of file.
 */
int skip_ws ( int comment )
{
    int c;
    while ( c = getchar() )
    {
        if ( c == '\n' || c == EOF ) return c;
	else if ( ! comment && ! isblank ( c ) )
	    return c;
    }
}

/* Skip non-whitespace until the next separator char-
 * acter (`(', `)', `,', `:', `\n'), whitespace, or EOF,
 * and return the characters skipped as a string.
 */
string read_symbol ( void )
{
    char buffer[200];
    char * p = buffer;
    char * result = NULL;
    unsigned length = 0;
        /* = strlen ( result ) or 0 if result is NULL.
	 */

    while ( 1 )
    {
	int c = getchar();
	if ( c == EOF ) break;
	if ( c == '(' || c == ')' ||
	     c == ',' || c == ':' ||
	     isspace ( c ) )
	{
	    ungetc ( c, stdin);
	    break;
	}
	* p ++ = c;
	if ( p - buffer >= sizeof ( buffer ) - 1 )
	{
	    unsigned extra = p - buffer;
	    result = realloc ( result,
	                       length + extra + 1 );
	    * p = 0;
	    strcpy ( result + length, buffer );
	    length += extra;
	    p = buffer;
	}
    }

    {
	unsigned extra = p - buffer;
	result = realloc ( result, length + extra + 1 );
	* p = 0;
	strcpy ( result + length, buffer );
    }

    return result;
}

/* Get a token which is either a symbol or a separator.
 * Line end is represented by the string "(END-OF-LINE)"
 * and end of file by the string "(END-OF-FILE)" so that
 * error messages are easy to print. 
 *
 * Backup may be set true to backup one token.
 *
 * Note that returned token is never empty.
 *
 * Also note that previous token is freed, and so must
 * be copied if you want to keep it.
 */
string ELINE = "(END-OF-LINE)";
string EFILE = "(END-OF-FILE)";
string OPENPAR = "(";
string CLOSEPAR = ")";
string COMMA = ",";
string COLON = ":";
string token;	/* Token is returned here.
                 * Initialized in main() to ELINE.
		 */
    /* We have set things up so you can use
     *     token == COMMA
     *     token == ELINE
     * to test for builtin separators, but must of
     * course use
     *     strcmp ( token, ... ) == 0
     * for non-separators.
     */
char * to_be_freed = NULL;
    /* Set to token if that was malloc'ed and set NULL
     * if token is quoted string constant.  Used to
     * free token.
     */
int backup = 0;
int line_number = 0;
static void error ( string message, ... );
void get_token ( void )
{
    int c;

    if ( backup )
    {
        backup = 0;
	return;
    }

    if ( token == ELINE )
    {
        while ( 1 )
	{
	    ++ line_number;
	    c = skip_ws ( 0 );

	    if ( c == '/' )
	    {
	        c = getchar();

		if ( c == EOF )
		    error ( "unexpected end of file" );
		else if ( c == '/' )
		{
		    skip_ws ( 1 );
		    continue;
		}
		else
		    error ( "unrecognized `/' at"
		            " beginning of line" );
		    /* We cannot backup 2 characters so
		     * we use the fact that the syntax
		     * does not allow /[^/] at the
		     * begining of a line (or anywhere
		     * for that matter).
		     */

	    } else if ( c == '\n' )
	        continue;

	    break;
	}
    }
    else
	c = skip_ws ( 0 );
    
    free ( to_be_freed );
    to_be_freed = NULL;

    if ( c == EOF )
	token = EFILE;
    else if ( c == '\n' )
	token = ELINE;
    else if ( c == '(' )
	token = OPENPAR;
    else if ( c == ')' )
	token = CLOSEPAR;
    else if ( c == ',' )
	token = COMMA;
    else if ( c == ':' )
	token = COLON;
    else
    {
	ungetc ( c, stdin );
	token = read_symbol();
	to_be_freed = (char *) token;
    }

    dprintf ( "{%s}", token );
}

int token_is ( string t )
{
    return eq ( token, t );
}

/* Print error message and exit.  We treat message as a
 * printf format.
 */
static void error ( string message, ... )
{
    va_list vlist;
    va_start ( vlist, message );

    printf ( "ERROR in line %d:\n", line_number );
    printf ( "      " );
    vprintf ( message, vlist );
    printf ( "\n" );
    exit ( 1 );
}

static void check_not_eof ( void )
{
   if ( token == EFILE )
      error ( "unexpected end of file" );
}

static double get_number ( void )
{
   double result;
   get_token();
   if ( ! to_number ( token, & result ) )
       error ( "expected number and got `%s'", token );
   return result;
}

/* Read token and check that it matches desired string.
 */
static void skip ( string desired )
{
    get_token();
    if ( ! token_is ( desired ) )
	error ( "expected `%s' but found `%s'",
	        desired, token );
}

static int is_variable ( void )
{
    return isalpha ( token[0] );
}

static void check_variable ( void )
{
    if ( ! is_variable() )
        error ( "`%s' is not a variable", token );
}

typedef struct {
    double x, y;
} Vector;
static Vector new_Vector ( double xval, double yval )
{
    Vector v;
    v.x = xval; v.y = yval;
    return v;
}
static void print_Vector ( Vector v )
{
    string x = to_string ( v.x );
    string y = to_string ( v.y );
    printf ( "(%s, %s)", x, y );
    free ( (char *) x );
    free ( (char *) y );
}
Vector negate ( Vector v )
{
    return new_Vector ( - v.x, - v.y );
}
Vector sum ( Vector v1, Vector v2 )
{
    return new_Vector ( v1.x + v2.x, v1.y + v2.y );
}
Vector difference ( Vector v1, Vector v2 )
{
    return new_Vector ( v1.x - v2.x, v1.y - v2.y );
}
double scalar_product ( Vector v1, Vector v2 )
{
    return v1.x * v2.x + v1.y * v2.y;
}
Vector multiple ( double s, Vector v )
{
    return new_Vector ( s * v.x, s * v.y );
}
double length ( Vector v )
{
    return sqrt ( v.x * v.x + v.y * v.y );
}
double angle ( Vector v )
{
    double result;

    /* We take extra care with angles that are
     * multiples of 90 degrees.  This is only
     * necessary if one is using exact equality
     * with integer coordinates instead of
     * approximate equality.
    */
    if ( v.x == 0 && v.y == 0 )
	error ( "angle of zero vector" );
    else if ( v.x == 0 )
	result = ( v.y > 0 ? +90 : -90 );
    else if ( v.y == 0 )
	result = ( v.x > 0 ? 0 : +180 );
    else
    {
	result = atan2 ( v.y, v.x );
	result *= 180.0 / M_PI;
    }
    return result;
}
Vector rotate ( Vector v, double angle ) 
{
    double sin_angle, cos_angle;

    /* We take extra care with angles that are
     * multiples of 90 degrees.  This is only
     * necessary if one is using exact equality
     * with integer coordinates instead of
     * approximate equality.
    */
    int k = (int) ( angle / 90 );
    if ( angle == k * 90 )
    {
	switch ( k % 4 )
	{
	case  0: sin_angle = 0; cos_angle = 1; break;
	case +1:
	case -3: sin_angle = 1; cos_angle = 0; break;
	case +2:
	case -2: sin_angle = 0; cos_angle = -1; break;
	case +3:
	case -1: sin_angle = -1; cos_angle = 0; break;
	default: abort();
	}
    }
    else
    {
	angle *= M_PI / 180;
	sin_angle = sin ( angle );
	cos_angle = cos ( angle );
    }
    return new_Vector
	( cos_angle * v.x - sin_angle * v.y,
	  sin_angle * v.x + cos_angle * v.y );
}

enum {
    BOOLEAN  = 1,
    SCALAR   = 2,
    VECTOR   = 3
};

typedef struct {
    int type;	/* BOOLEAN, SCALAR, or VECTOR. */
    int b;	/* Value if BOOLEAN.           */
    double s;	/* Value if SCALAR.            */
    Vector v;	/* Value if VECTOR.            */
} Value;

static void print_Value ( Value v )
{
    if ( v.type == BOOLEAN )
        printf ( v.b ? "true" : "false" );
    else if ( v.type == SCALAR )
    {
        string s = to_string ( v.s );
	printf ( "%s", s );
	free ( (char *) s );
    }
    else if ( v.type == VECTOR )
	print_Vector ( v.v );
    else
	printf ( "BAD OBJECT TYPE %d", v.type );
}

/* We implement the variable table as a simple list that
 * is searched linearly.  The hcreate(3) alternative may
 * fail if we do not correctly guess the maximum number
 * of entries, so we do not use it.
 */
typedef struct Entry_struct
{
    string name;
    Value v;
    struct Entry_struct * next;
} Entry;
Entry * variable_table = NULL;

/* Return variable_table entry matching `name', or NULL
 * if none.
 */
static Entry * find ( string name )
{
    Entry * result = variable_table;
    while ( result != NULL
            &&
	    ! eq ( result->name, name ) )
        result = result->next;
    return result;
}
/* Set variable_table entry matching `name' to value
 * `v', creating entry if it did not exist.  Also we
 * either free or use `name'.
 */
static void set ( string name, Value v )
{
    Entry * e = find ( name );
    if ( e == NULL )
    {
        e = (Entry *) malloc ( sizeof ( Entry ) );
	e->name = name;
	e->next = variable_table;
	variable_table = e;
    }
    else free ( (char *) name );
    e->v = v;
}
/* Remove any variable_table entry matching `name'.  Do
 * nothing if no entry exists.
 */
static void clear ( string name )
{
    Entry ** ep = & variable_table;
    while ( * ep != NULL )
    {
        if ( eq ( (*ep)->name, name ) )
	{
	    Entry * e = * ep;
	    * ep = (*ep)->next;
	    free ( (char *) e->name );
	    free ( e );
	    return;
	}
	ep = & (*ep)->next;
    }
}
/* Empty the variable_table completely.
 */
static void clear_all ( void )
{
    Entry * e = variable_table;
    while ( e != NULL )
    {
        Entry * n = e->next;
	free ( (char *) e->name );
	free ( e );
	e = n;
    }
    variable_table = NULL;
}

static void require_boolean ( Value v1 )
{
    if ( v1.type != BOOLEAN )
	error ( "operand should be boolean" );
}
static void require_booleans ( Value v1, Value v2 )
{
    if ( v1.type != BOOLEAN )
	error
	    ( "first operand should be boolean" );
    else if ( v2.type != BOOLEAN )
	error
	    ( "second operand should be boolean" );
}
static void require_scalar ( Value v1 )
{
    if ( v1.type != SCALAR )
	error ( "operand should be scalar" );
}
static void require_scalars ( Value v1, Value v2 )
{
    if ( v1.type != SCALAR )
	error ( "first operand should be scalar" );
    else if ( v2.type != SCALAR )
	error ( "second operand should be scalar" );
}
static void require_vector ( Value v1 )
{
    if ( v1.type != VECTOR )
	error ( "operand should be vector" );
}
static void require_vectors ( Value v1, Value v2 )
{
    if ( v1.type != VECTOR )
	error ( "first operand should be vector" );
    else if ( v2.type != VECTOR )
	error ( "second operand should be vector" );
}
static void require_scalar_vector
	( Value v1, Value v2 )
{
    if ( v1.type != SCALAR )
	error ( "first operand should be scalar" );
    else if ( v2.type != VECTOR )
	error ( "second operand should be vector" );
}
static void require_vector_scalar
	( Value v1, Value v2 )
{
    if ( v1.type != VECTOR )
	error ( "first operand should be vector" );
    else if ( v2.type != SCALAR )
	error ( "second operand should be scalar" );
}

/* Require v1 to be SCALAR or VECTOR and return
 * true if SCALAR, false if VECTOR.
 */
static int is_scalar ( Value v1 )
{
    if ( v1.type == SCALAR )
	return 1;
    else if ( v1.type == VECTOR )
	return 0;
    else
	error
	  ( "operand should be scalar or vector" );
}

/* Require v1 and v2 to be BOTH SCALAR or BOTH
 * VECTOR and return true if SCALAR, false if
 * VECTOR.
 */
static int are_scalar ( Value v1, Value v2 )
{
    if ( v1.type != v2.type )
	error ( "operands should both be scalar"
		" or both be vector" );
    else if ( v1.type == SCALAR )
	return 1;
    else if ( v1.type == VECTOR )
	return 0;
    else
	error
	  ( "operands should be scalar or vector" );
    }

/* Reads a constant value and returns its Value,
 * or a variable with a value and returns a its
 * Value.
 */
static Value get_value ( )
{
    Value v;

    get_token();
    if ( token == OPENPAR )
    {
	double x, y;
	v.type = VECTOR;
	x = get_number();
	skip ( COMMA );
	y = get_number();
	skip ( CLOSEPAR) ;
	v.v = new_Vector ( x, y );
    }
    else if ( token_is ( "true" ) )
    {
	v.type = BOOLEAN;
	v.b = 1;
    }
    else if ( token_is ( "false" ) )
    {
	v.type = BOOLEAN;
	v.b = 0;
    }
    else if ( is_variable() )
    {
        Entry * e = find ( token );
        if ( e == NULL )
	    error ( "`%s' unassigned", token );
	v = e->v;
    }
    else if ( to_number ( token, & v.s ) )
	v.type = SCALAR;
    else
	error ( "expected true, false, "
		" scalar constant, "
		" vector constant, "
		" or variable but got `%s'",
		token );

    if ( debug )
    {
        printf ( "[" );
        print_Value ( v );
        printf ( "]" );
    }
    return v;
}

/* Execute `clear ...' statement after `clear' token
 * has been read and skipped.
 */
static void execute_clear ( )
{
    int found = 0;
    while ( 1 )
    {
	get_token();
	if ( token == ELINE ) break;
	check_variable();
	clear ( token );
	found = 1;
    }
    if ( ! found )
        clear_all();
}

/* Execute `print{ln} ...' statement after
 * `print{ln}' token has been read and skipped,
 * BUT do not output final space or line end.
 */
static void execute_print ( )
{
    int first = 1;
    while ( 1 )
    {
	get_token();
	if ( token == ELINE ) break;
	if ( first )
	    first = 0;
	else
	    printf ( " " );

	{
	    Entry * e = find ( token );
	    if ( e == NULL )
	        printf ( "%s", token );
	    else
	        print_Value ( e->v );
	}
    }
}

/* Execute `variable = ...' statement after
 * `variable =' tokens have been read and skipped.
 * NOTE: Variable must be a dup'ed string not otherwise
 * used.
 */
static void execute_assign ( string variable )
{
    Value v1;
        /* This is both the first value read and the
	 * final resulting value.
	 */
    if ( eq ( variable, "true" )
	 ||
	 eq ( variable, "false" ) )
	error ( "attempt to assign a value to `%s'",
		variable );

    /* Read and process statement up to but not
     * including the statement ending EOL.
     */
    get_token();
    if ( token_is ( "-" ) )
    {
	v1 = get_value();
	if ( is_scalar ( v1 ) )
	    v1.s = - v1.s;
	else
	    v1.v = negate ( v1.v );
    }
    else if ( token_is ( "|" ) )
    {
	v1 = get_value();
	require_scalar ( v1 );
	skip ( "|" );
	v1.s = fabs ( v1.s );
    }
    else if ( token_is ( "||" ) )
    {
	v1 = get_value();
	require_vector ( v1 );
	skip ( "||" );
	v1.s = length ( v1.v );
	v1.type = SCALAR;
    }
    else if ( token_is ( "angle" ) )
    {
	v1 = get_value();
	require_vector ( v1 );
	v1.s = angle ( v1.v );
	v1.type = SCALAR;
    }
    else if ( token_is ( "!" ) )
    {
	v1 = get_value();
	require_boolean ( v1 );
	v1.b = ! v1.b;
    }
    else
    {
        /* Case where there is either a binary operator
	 * or no operator.
	 */
	backup = 1;
	v1 = get_value();
	get_token();

	if ( token_is ( "+" ) )
	{
	    Value v2 = get_value();
	    if ( are_scalar ( v1, v2 ) )
		v1.s += v2.s;
	    else
		v1.v = sum ( v1.v, v2.v );
	}
	else if ( token_is ( "-" ) )
	{
	    Value v2 = get_value();
	    if ( are_scalar ( v1, v2 ) )
		v1.s -= v2.s;
	    else
		v1.v = difference ( v1.v, v2.v );
	}
	else if ( token_is ( "*" ) )
	{
	    Value v2 = get_value();
	    if ( is_scalar ( v1 ) )
	    {
		if ( is_scalar ( v2 ) )
		    v1.s *= v2.s;
		else
		{
		    v1.v = multiple ( v1.s, v2.v );
		    v1.type = VECTOR;
		}
	    }
	    else
	    {
		require_vectors ( v1, v2 );
		v1.s = scalar_product ( v1.v, v2.v );
		v1.type = SCALAR;
	    }
	}
	else if ( token_is ( "/" ) )
	{
	    Value v2 = get_value();
	    require_scalars ( v1, v2 );
	    if ( v2.s == 0 )
		error ( "zero divisor" );
	    v1.s /= v2.s;
	}
	else if ( token_is ( "^" ) )
	{
	    Value v2 = get_value();
	    require_vector_scalar ( v1, v2 );
	    v1.v = rotate ( v1.v, v2.s );
	}
	else if ( token_is ( "&&" ) )
	{
	    Value v2 = get_value();
	    require_booleans ( v1, v2 );
	    v1.b = v1.b && v2.b;
	}
	else if ( token_is ( "||" ) )
	{
	    Value v2 = get_value();
	    require_booleans ( v1, v2 );
	    v1.b = v1.b || v2.b;
	}
	else if ( token_is ( "==" ) )
	{
	    Value v2 = get_value();
	    require_scalars ( v1, v2 );
	    v1.b = ( v1.s == v2.s );
	    v1.type = BOOLEAN;
	}
	else if ( token_is ( "!=" ) )
	{
	    Value v2 = get_value();
	    require_scalars ( v1, v2 );
	    v1.b = ( v1.s != v2.s );
	    v1.type = BOOLEAN;
	}
	else if ( token_is ( "<" ) )
	{
	    Value v2 = get_value();
	    require_scalars ( v1, v2 );
	    v1.b = ( v1.s < v2.s );
	    v1.type = BOOLEAN;
	}
	else if ( token_is ( "<=" ) )
	{
	    Value v2 = get_value();
	    require_scalars ( v1, v2 );
	    v1.b = ( v1.s <= v2.s );
	    v1.type = BOOLEAN;
	}
	else if ( token_is ( ">" ) )
	{
	    Value v2 = get_value();
	    require_scalars ( v1, v2 );
	    v1.b = ( v1.s > v2.s );
	    v1.type = BOOLEAN;
	}
	else if ( token_is ( ">=" ) )
	{
	    Value v2 = get_value();
	    require_scalars ( v1, v2 );
	    v1.b = ( v1.s >= v2.s );
	    v1.type = BOOLEAN;
	}
	else if ( token != ELINE )
	    error ( "`%s' unrecognized", token );
	else backup = 1;
    }

    /* Skip statement ending ELINE.
     */
    skip ( ELINE );

    set ( variable, v1 );

    dprintf ( "ASSIGN " );
    if ( debug ) print_Value ( v1 );
    dprintf ( " TO %s\n", variable );
}


int main ( int argc, char * argv[] )
{
    debug = ( argc > 1 );

    /* Loop to read and execute a statement.
     */
    token = ELINE;
    while ( 1 )
    {
	get_token();
	if ( token == EFILE ) break;

	if ( token_is ( "if" ) )
	{
	    /* Process `if' statement.  If condition is
	     * true, just skip past `:'.  Otherwise skip
	     * past ELINE and go to next statement.
	     */
	    Value v = get_value();
	    require_boolean ( v );
	    skip ( ":" );
	    if ( ! v.b )
	    {
		while ( 1 )
		{
		    get_token();
		    check_not_eof();
		    if ( token == ELINE )
			break;
		}
		continue;
	    }
	    get_token();
	}

	if ( token_is ( "clear" ) )
	    execute_clear();
	else if ( token_is ( "print" ) )
	{
	    execute_print();
	    printf ( " " );
	}
	else if ( token_is ( "println" ) )
	{
	    execute_print();
	    printf ( "\n" );
	}
	else if ( is_variable() )
	{
	    string variable = strdup ( token );
	    skip ( "=" );
	    execute_assign ( variable );
	}
	else if ( token != ELINE )
	    error ( "`%s' unrecognized", token );
    }

    return 0;
}
