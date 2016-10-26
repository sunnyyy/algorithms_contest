/* Generate Binary Tree Sort Problem Data
 *
 * File:     make_bintreesort_input.c
 * Author:   Bob Walton <walton@deas.harvard.edu>
 * Date:     Wed Apr  2 20:51:37 EDT 2014
 *
 * The authors have placed this program in the public
 * domain; they make no warranty and accept no liability
 * for this program.
 *
 * RCS Info (may not be true date or author):
 *
 *   $Author: walton $
 *   $Date: 2014/04/03 11:17:19 $
 *   $RCSfile: make_bintreesort_input.c,v $
 *   $Revision: 1.4 $
 *
 * Input:
 *
 *	For each case, a line with the test case name
 *	followed by the following line:
 *
 *	    N M pAin pAout pRin pRout pPin SEED
 *
 *	Output for the case is a bintreesort test case
 *	with the given test case name and data generated
 *	according to the second input line as follows.
 *	N is the maximum number of distinct numbers in
 *	the test case.  M <= N is the maximum number of
 *	numbers in test case data set at any one time.
 *	The pXyyy's are the probabilities that the next
 *	command will be an X command with a number that
 *	is xxx=`in' or xxx=`out' of the data set at the
 *	time the command is given.  Here
 *
 *	  pPout = 1 - pAin - pAout - pRin - pRout - pPin
 *
 *      SEED is the random number generator seed.
 *
 *	It is required that pAout > pRin so numbers are
 *	added to the data set until there are M in the
 *	data set, at which point the following switches
 *	occur:
 *
 *		pAin    <--->   pRout
 *		pAout   <--->   pRin
 *
 *      Then if C1 commands have previously been issued,
 *      then C2 more commands are issued, where C2 is
 *      choosen randomly and uniformly in the range
 *      [0,C1].
 *
 *      Also, whenever a command that will not work
 *      properly is to be output, that output is sup-
 *      pressed.  This includes Xin commands when the
 *      data set is empty, Aout commands when the data
 *      set has M numbers, and Xout commands when the
 *      dataset has N numbers (only happens if M == N).
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

int debug = 0;
#define dprintf if ( debug ) printf

#define FOR(i,n) for (i = 0; i < (n); ++ i)

/* Maximum allowed value of N and M.
 */
#define MAX_M 1000000
#define MAX_N 10000000
#define MAX_LINE 80

char name[MAX_LINE+3];
int M, N;
double pAin, pAout, pRin, pRout, pPin, pPout;
unsigned SEED;

/* We begin a test case by computing N 15 digit distinct
 * random numbers in `numbers[0 .. N-1]'.
 */
typedef double number;
number numbers[2*MAX_N+1];

void compute_numbers ( void )
{
    /* We proceed by computing N numbers and inserting
     * them into a hash table * of size 2 * N + 1.
     * Unused hash table entries are set to -1.  The
     * hashing function of i is just i % ( 2 * N + 1),
     * which works since the i is random.  The hash
     * table serves to prevent numbers from being
     * duplicated.
     */
    int hsize = 2 * N + 1;
    int n, i;
    FOR ( n, hsize ) numbers[n] = -1;
    n = 0;
    while ( n < N )
    {
	int d, h;
	number num = 0;
        FOR ( d, 15 )
	{
	    num *= 10;
	    num += rand() % 10;
	}
	h = (int) fmod ( num, hsize );
	assert ( 0 <= h && h < hsize );
	while ( numbers[h] != -1 )
	{
	    if ( numbers[h] == num )
	    {
	        h = -1;
		break;
	    }
	    ++ h;
	    if ( h >= hsize ) h = 0;
	}
	if ( h < 0 ) continue;
	numbers[h] = num;
	++ n;
    }

    /* Now compact the numbers into the first N elements
     * of `numbers'.
     */
    n = 0;
    FOR ( i, hsize )
    {
        if ( numbers[i] != -1 )
	    numbers[n++] = numbers[i];
    }
	  
    
}

/* The numbers in `numbers[0 .. m-1]' are in the data
 * base and the numbers in `numbers[m .. N-1]' are not.
 */
int m;

/* The following output the given commands and update m
 * and `numbers' accordingly, and return 1 on success
 * and 0 on failure (such as A # when data base already
 * has M elements).
 */

int Ain ( void )
{
    int i;
    if ( m == 0 ) return 0;
    i = rand() % m;
    printf ( "A %.0f\n", numbers[i] );
    return 1;
}

int Aout ( void )
{
    int i; number n;
    if ( m == M ) return 0;
    i = m + rand() % ( N - m );
    printf ( "A %.0f\n", numbers[i] );
    n = numbers[m];
    numbers[m++] = numbers[i];
    numbers[i] = n;
    return 1;
}

int Rin ( void )
{
    int i; number n;
    if ( m == 0 ) return 0;
    i = rand() % m;
    printf ( "R %.0f\n", numbers[i] );
    n = numbers[i];
    numbers[i] = numbers[--m];
    numbers[m] = n;
    return 1;
}

int Rout ( void )
{
    int i;
    if ( m == N ) return 0;
    i = m + rand() % ( N - m );
    printf ( "R %.0f\n", numbers[i] );
    return 1;
}

int Pin ( void )
{
    int i;
    if ( m == 0 ) return 0;
    i = rand() % m;
    printf ( "P %.0f\n", numbers[i] );
    return 1;
}

int Pout ( void )
{
    int i;
    if ( m == N ) return 0;
    i = m + rand() % ( N - m );
    printf ( "P %.0f\n", numbers[i] );
    return 1;
}

/* Output random commands:
 *
 *     if c == 0: until m == M
 *     if c > 0:  until c commands have been output
 *     
 * Return number of commands output.
 */
int output_commands ( int c )
{
    int o = 0;
    while ( 1 )
    {
        double p = ( (double) rand() ) / RAND_MAX;

	if ( p <= pAin ) o += Ain();
	else if ( p <= pAin + pAout ) o += Aout();
	else if ( p <= pAin + pAout + pRin ) o += Rin();
	else if ( p <= pAin + pAout + pRin + pRout )
	    o += Rout();
	else if ( p <= pAin + pAout + pRin + pRout
	                            + pPin )
	    o += Pin();
	else
	    o += Pout();

        if ( c == 0 )
	{
	    if ( m == M ) break;
	}
	else if ( o == c ) break;
    }
    
    return o;
}


/* Main program
 */
int main(int argc, char * argv[])
{
    debug = ( argc > 1 );

    while ( fgets ( name, sizeof ( name ), stdin) )
    {
        int c; double temp;

        assert ( strlen ( name ) <= MAX_LINE + 1 );
	printf("%s", name);

	scanf ( "%d %d %lf %lf %lf %lf %lf %u",
	        & N, & M, & pAin, & pAout,
		          & pRin, & pRout,
			  & pPin, & SEED );
	fgets ( name, sizeof ( name ), stdin) ;
	assert ( name[0] == '\n' );

	assert ( 0 < N && N <= MAX_N );
	assert ( 0 < M && M <= MAX_M );
	assert ( M <= N );
	assert ( 0.0 <= pAin && pAin <= 1.0 );
	assert ( 0.0 <= pAout && pAout <= 1.0 );
	assert ( 0.0 <= pRin && pRin <= 1.0 );
	assert ( 0.0 <= pRout && pAout <= 1.0 );
	assert ( 0.0 <= pPin && pPin <= 1.0 );
	double pPout = 1.0 - pAin - pAout
	             - pRin - pRout - pPin;
	assert ( 0.0 <= pPout && pPout <= 1.0 );
	assert ( pRin < pAout );
	assert ( SEED > 0 );

	srand ( SEED );

	compute_numbers();
	m = 0;
	c = output_commands ( 0 );
	dprintf ( "COMMANDS = %d\n", c );
	temp = pAin; pAin = pRout; pRout = temp;
	temp = pAout; pAout = pRin; pRin = temp;
	output_commands ( rand() % ( c + 1 ) );
	printf ( "E\n" );
    }

    return 0;
}

