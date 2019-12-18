#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rofi_int_matcher ;
struct TYPE_2__ {int /*<<< orphan*/  tokenize; } ;

/* Variables and functions */
 TYPE_1__ config ; 
 int /*<<< orphan*/ * create_regex (char const*,int) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/ ** g_malloc0 (int) ; 
 int /*<<< orphan*/ ** g_realloc (int /*<<< orphan*/ **,int) ; 
 char* g_strdup (char const*) ; 
 size_t strlen (char const*) ; 
 char* strtok_r (char*,char const* const,char**) ; 

rofi_int_matcher **helper_tokenize ( const char *input, int case_sensitive )
{
    if ( input == NULL ) {
        return NULL;
    }
    size_t len = strlen ( input );
    if ( len == 0 ) {
        return NULL;
    }

    char             *saveptr = NULL, *token;
    rofi_int_matcher **retv = NULL;
    if ( !config.tokenize ) {
        retv    = g_malloc0 ( sizeof ( rofi_int_matcher* ) * 2 );
        retv[0] = create_regex ( input, case_sensitive );
        return retv;
    }

    // First entry is always full (modified) stringtext.
    int num_tokens = 0;

    // Copy the string, 'strtok_r' modifies it.
    char *str = g_strdup ( input );

    // Iterate over tokens.
    // strtok should still be valid for utf8.
    const char * const sep = " ";
    for ( token = strtok_r ( str, sep, &saveptr ); token != NULL; token = strtok_r ( NULL, sep, &saveptr ) ) {
        retv                 = g_realloc ( retv, sizeof ( rofi_int_matcher* ) * ( num_tokens + 2 ) );
        retv[num_tokens]     = create_regex ( token, case_sensitive );
        retv[num_tokens + 1] = NULL;
        num_tokens++;
    }
    // Free str.
    g_free ( str );
    return retv;
}