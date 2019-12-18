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
 int /*<<< orphan*/  EnsureUTF8 (char*) ; 
 int /*<<< orphan*/ * strchr (char*,unsigned char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

void filename_sanitize( char *str )
{
    unsigned char c;

    /* Special file names, not allowed */
    if( !strcmp( str, "." ) || !strcmp( str, ".." ) )
    {
        while( *str )
            *(str++) = '_';
        return;
    }

    /* On platforms not using UTF-8, VLC cannot access non-Unicode paths.
     * Also, some file systems require Unicode file names.
     * NOTE: This may inserts '?' thus is done replacing '?' with '_'. */
    EnsureUTF8( str );

    /* Avoid leading spaces to please Windows. */
    while( (c = *str) != '\0' )
    {
        if( c != ' ' )
            break;
        *(str++) = '_';
    }

    char *start = str;

    while( (c = *str) != '\0' )
    {
        /* Non-printable characters are not a good idea */
        if( c < 32 )
            *str = '_';
        /* This is the list of characters not allowed by Microsoft.
         * We also black-list them on Unix as they may be confusing, and are
         * not supported by some file system types (notably CIFS). */
        else if( strchr( "/:\\*\"?|<>", c ) != NULL )
            *str = '_';
        str++;
    }

    /* Avoid trailing spaces also to please Windows. */
    while( str > start )
    {
        if( *(--str) != ' ' )
            break;
        *str = '_';
    }
}