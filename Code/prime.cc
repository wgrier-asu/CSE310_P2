///////////////////////////////////////////////////////////////////////////////
//
//  This implments a brute force method of determining the prime numbers
//  in a given range 1..n.
//
///////////////////////////////////////////////////////////////////////////////

#include	<cstdio>
#include	<math.h>

bool isPrime( int val )
{
    int limit, factor = 2;

    limit = (long)( sqrtf( (float) val ) + 0.5f );
    while( (factor <= limit) && (val % factor) )
        factor++;

    return( factor > limit );
}

/* firstPrime function
 * Description: Returns the first prime after integer k */
int firstPrime(int k){
    while(!isPrime(k)) k++;
    return k;
}




int prime()
{
    int i, n, p;

    printf( "Enter number n of numbers to test as primes.\n" );
    scanf( "%d", &n );
    printf( "Now enter %d numbers to test as prime.\n", n );
    fflush( stdout );

    for( i = 0; i < n; i++ ){
        printf( "Enter number:\n" );
        scanf( "%d", &p );

        if( isPrime( p ) )
            printf( "%d is a prime.\n", p );
        else
            printf( "%d is not a prime.\n", p );
    }

    return 1;
}

