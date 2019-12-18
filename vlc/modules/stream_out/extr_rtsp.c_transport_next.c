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
 char* strchr (char const*,char const) ; 

__attribute__((used)) static inline const char *transport_next( const char *str )
{
    /* Looks for comma */
    str = strchr( str, ',' );
    if( str == NULL )
        return NULL; /* No more transport options */

    str++; /* skips comma */
    while( strchr( "\r\n\t ", *str ) )
        str++;

    return (*str) ? str : NULL;
}