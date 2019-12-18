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
 int* inverse ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ isxdigit (unsigned char) ; 
 int toupper (unsigned char) ; 

__attribute__((used)) static int load_byte( unsigned char encoding_type,
                      unsigned char *output, char **input,
                      unsigned char *j, unsigned char *k )
{
    *output = 0;

    if( encoding_type == 1 )
    {
        if( isxdigit( (unsigned char)**input ) == 0 )
            return -1;

        if( isdigit( (unsigned char)**input ) == 0 )
            *output = (toupper( (unsigned char)**input ) - 7) * 16;
        else
            *output = **input * 16;

        (*input)++;

        if( isxdigit( (unsigned char)**input ) == 0 )
            return -1;

        if( isdigit( (unsigned char)**input ) == 0 )
            *output |= toupper( (unsigned char)**input ) - 0x37;
        else
            *output |= **input - 0x30;

        (*input)++;
    }
    else if( encoding_type == 2 )
    {
        unsigned char **uinput = (unsigned char **)input;

        if( **uinput > 127 || inverse[ **uinput ] == 0xFF )
            return -1;

        if( *k == 0 )
        {
            if( (*uinput)[ 1 ] > 127 || inverse[ (*uinput)[ 1 ] ] == 0xFF )
                return -1;

            *output = (inverse[ (*uinput)[ 0 ] ] * 4) |
                        (inverse[ (*uinput)[ 1 ] ] / 16);

            *j = inverse[ (*uinput)[ 1 ] ] * 16;
            *k = 4;

            (*uinput) += 2;
        }
        else if( *k == 2 )
        {
            *output = *j | inverse[ **uinput ];

            *j = 0;
            *k = 0;

            (*uinput)++;
        }
        else if( *k == 4 )
        {
            *output = (inverse[ **uinput ] / 4) | *j;

            *j = inverse[ **uinput ] * 64;
            *k = 2;

            (*uinput)++;
        }
    }

    return 0;
}