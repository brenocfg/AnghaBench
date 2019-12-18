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
 unsigned int* ft2_errorindex ; 
 char const** ft2_errorstrings ; 
 unsigned int ft2_num_errors ; 

const char *ft2_strerror(unsigned err)
{
    unsigned i;
    for( i=0; i<ft2_num_errors; ++i )
        if( err==ft2_errorindex[i] )
            break;

    return i<ft2_num_errors ? ft2_errorstrings[i] :
           "An error freetype2 neglected to specify";
}