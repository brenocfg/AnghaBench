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
 scalar_t__ IsEscapeNeeded (char const) ; 
 char* malloc (size_t) ; 
 scalar_t__ unlikely (int) ; 

char *config_StringEscape( const char *str )
{
    size_t length = 0;

    if( str == NULL )
        return NULL;

    for( const char *p = str; *p; p++ )
        length += IsEscapeNeeded( *p ) ? 2 : 1;

    char *ret = malloc( length + 1 ), *dst = ret;

    if( unlikely( !ret ) )
        return NULL;

    for( const char *p = str; *p; p++ )
    {
        if( IsEscapeNeeded( *p ) )
            *dst++ = '\\';
        *dst++ = *p;
    }
    *dst = '\0';;
    return ret;
}