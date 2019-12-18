#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  strspn (char const*,char*) ; 
 long long strtol (char const*,char**,int) ; 

long long int strtoll( const char *nptr, char **endptr, int base )
{
    long long i_value = 0;
    int sign = 1, newbase = base ? base : 10;

    nptr += strspn( nptr, "\t " );
    if( *nptr == '-' )
    {
        sign = -1;
        nptr++;
    }

    /* Try to detect base */
    if( *nptr == '0' )
    {
        newbase = 8;
        nptr++;

        if( *nptr == 'x' )
        {
            newbase = 16;
            nptr++;
        }
    }

    if( base && newbase != base )
    {
        if( endptr ) *endptr = (char *)nptr;
        return i_value;
    }

    switch( newbase )
    {
        case 10:
            while( *nptr >= '0' && *nptr <= '9' )
            {
                i_value *= 10;
                i_value += ( *nptr++ - '0' );
            }
            if( endptr ) *endptr = (char *)nptr;
            break;

        case 16:
            while( (*nptr >= '0' && *nptr <= '9') ||
                   (*nptr >= 'a' && *nptr <= 'f') ||
                   (*nptr >= 'A' && *nptr <= 'F') )
            {
                int i_valc = 0;
                if(*nptr >= '0' && *nptr <= '9') i_valc = *nptr - '0';
                else if(*nptr >= 'a' && *nptr <= 'f') i_valc = *nptr - 'a' +10;
                else if(*nptr >= 'A' && *nptr <= 'F') i_valc = *nptr - 'A' +10;
                i_value *= 16;
                i_value += i_valc;
                nptr++;
            }
            if( endptr ) *endptr = (char *)nptr;
            break;

        default:
            i_value = strtol( nptr, endptr, newbase );
            break;
    }

    return i_value * sign;
}