#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    /* UNSIGNED TYPES */
    printf("\n\tUNSIGNED TYPES\n");
    printf("UNSIGNED CHAR:  %d      %d\n", 0, UCHAR_MAX);
    printf("UNSIGNED SHORT: %d      %d\n", 0, USHRT_MAX);
    printf("UNSIGNED INT:   %lu      %lu\n", 0, UINT_MAX);
    printf("UNSIGNED LONG:  %lu      %lu\n", 0, ULONG_MAX);
    
    /* SIGNED TYPES */
    printf("\n\tSIGNED TYPES\n");
    printf("SIGNED CHAR:  %li     %li\n", SCHAR_MIN, SCHAR_MAX);
    printf("SIGNED SHORT: %li     %li\n", SHRT_MIN, SHRT_MAX);
    printf("SIGNED INT:   %li     %li\n", INT_MIN, INT_MAX);
    printf("SIGNED LONG:  %li     %li\n\n", LONG_MIN, LONG_MAX);
    
    /* FLOAT & DOUBLE TYPES */
    printf("FLOAT:            %lf     %lf\n", FLT_MIN, FLT_MAX);
    printf("FLOAT EXPONENTS:  %i     %i\n", FLT_MIN_EXP, FLT_MAX_EXP);
    printf("DOUBLE:           %Lf     %Lf\n", DBL_MIN, DBL_MAX);
    printf("DOUBLE EXPONENTS: %i     %i\n", DBL_MIN_EXP, DBL_MAX_EXP);
}