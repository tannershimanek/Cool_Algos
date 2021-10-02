// Fast Inverse Square Root
// Typically a developer would run 1/sqrt(x). However, Here is a faster solution.
// https://www.youtube.com/watch?v=p8u_k2LIZyo&t=328s

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

float Q_rsqrt( float number );
float C_rsqrt( float number );


int main( int argc, char *argv[] )  /* main driver function */
{
    float Q_result, C_result;
    float arg = atof(argv[1]);

    Q_result = Q_rsqrt(arg);
    C_result = C_rsqrt(arg);
    
    printf("Value: %s\n", argv[1]);
    printf("Normal: %9.6f\n", C_result);
    printf("Fast: %9.6f\n", Q_result);
}

// Note: log2( 1 + x ) = x + mu -- per logrithmic laws
// Look into IEEE 754 for more information

float Q_rsqrt( float number )   /* cool algo starts here */
{
    long i;                             /* 32-bit number */
    float x2, y;                        /* 32-bit decimal number */
    const float threehalfs = 1.5F;      /* 1.5 (also 32-bit) */

    x2 = number * 0.5f;
    y  = number;
    i  = * ( long * ) &y;                        /* get address of float and convert the address to a long address (c will think the number is a long) */
    i  = 0x5f3759df - ( i >> 1 );                /* bit shift once to the right */
    y  = * ( float * ) &i;                       /* reverse the steps of the bit hack above */
    y  = y * ( threehalfs - ( x2 * y * y ) );    /* Newtons method -- first iteration -- error of 1% */
    y  = y * ( threehalfs - ( x2 * y * y ) );    /* second iteration, can be removed -- notice no division, division is slow. */
    
    return y;
}


float C_rsqrt( float number )   /* regular inverse square root */
{
    return 1 / sqrt(number);
}




/*
 * Bit shifting tricks
 *
 * 110  = 6
 * 1100 = 12  --  shifting left 1 bit doubles
 * 11   = 3   --  shifting right 1 but halves
 *
 * 111  = 7
 * 1100 = 14
 * 11   = 3   --  remmber that if the number is odd, it rounds
 *
 */

