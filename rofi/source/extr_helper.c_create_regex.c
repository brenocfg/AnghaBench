#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int invert; int /*<<< orphan*/ * regex; } ;
typedef  TYPE_1__ rofi_int_matcher ;
typedef  char const gchar ;
struct TYPE_6__ {char const matching_negate_char; int matching_method; } ;
typedef  int /*<<< orphan*/  GRegex ;

/* Variables and functions */
#define  MM_FUZZY 130 
#define  MM_GLOB 129 
#define  MM_REGEX 128 
 int /*<<< orphan*/ * R (char const*,int) ; 
 TYPE_4__ config ; 
 char* fuzzy_to_regex (char const*) ; 
 int /*<<< orphan*/  g_free (char const*) ; 
 TYPE_1__* g_malloc0 (int) ; 
 char* g_regex_escape_string (char const*,int) ; 
 char* glob_to_regex (char const*) ; 

__attribute__((used)) static rofi_int_matcher * create_regex ( const char *input, int case_sensitive )
{
    GRegex           * retv = NULL;
    gchar            *r;
    rofi_int_matcher *rv = g_malloc0 ( sizeof ( rofi_int_matcher ) );
    if ( input && input[0] == config.matching_negate_char ) {
        rv->invert = 1;
        input++;
    }
    switch ( config.matching_method )
    {
    case MM_GLOB:
        r    = glob_to_regex ( input );
        retv = R ( r, case_sensitive );
        g_free ( r );
        break;
    case MM_REGEX:
        retv = R ( input, case_sensitive );
        if ( retv == NULL ) {
            r    = g_regex_escape_string ( input, -1 );
            retv = R ( r, case_sensitive );
            g_free ( r );
        }
        break;
    case MM_FUZZY:
        r    = fuzzy_to_regex ( input );
        retv = R ( r, case_sensitive );
        g_free ( r );
        break;
    default:
        r    = g_regex_escape_string ( input, -1 );
        retv = R ( r, case_sensitive );
        g_free ( r );
        break;
    }
    rv->regex = retv;
    return rv;
}