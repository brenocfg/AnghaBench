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
typedef  int ssize_t ;
typedef  char gchar ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 char* g_memdup (char const*,int) ; 
 int /*<<< orphan*/  g_string_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  g_string_append_len (int /*<<< orphan*/ *,char const*,int) ; 
 char* g_string_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_string_sized_new (int) ; 
 scalar_t__ g_utf8_validate (char const*,int,char const**) ; 

char * rofi_force_utf8 ( const gchar *data, ssize_t length )
{
    if ( data == NULL ) {
        return NULL;
    }
    const char *end;
    GString    *string;

    if ( g_utf8_validate ( data, length, &end ) ) {
        return g_memdup ( data, length + 1 );
    }
    string = g_string_sized_new ( length + 16 );

    do {
        /* Valid part of the string */
        g_string_append_len ( string, data, end - data );
        /* Replacement character */
        g_string_append ( string, "\uFFFD" );
        length -= ( end - data ) + 1;
        data    = end + 1;
    } while ( !g_utf8_validate ( data, length, &end ) );

    if ( length ) {
        g_string_append_len ( string, data, length );
    }

    return g_string_free ( string, FALSE );
}