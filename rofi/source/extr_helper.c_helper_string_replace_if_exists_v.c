#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  GRegex ;
typedef  int /*<<< orphan*/  GHashTable ;
typedef  TYPE_1__ GError ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  g_error_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/ * g_regex_new (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 char* g_regex_replace_eval (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  g_regex_unref (int /*<<< orphan*/ *) ; 
 char* g_strdup_printf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  helper_eval_cb2 ; 
 int /*<<< orphan*/  rofi_view_error_dialog (char*,int /*<<< orphan*/ ) ; 

char *helper_string_replace_if_exists_v ( char * string, GHashTable *h )
{
    GError  *error = NULL;
    char    *res   = NULL;

    // Replace hits within {-\w+}.
    GRegex *reg = g_regex_new ( "\\[(.*)({[-\\w]+})(.*)\\]|({[\\w-]+})", 0, 0, &error );
    if ( error == NULL ){
        res = g_regex_replace_eval ( reg, string, -1, 0, 0, helper_eval_cb2, h, &error );
    }
    // Free regex.
    g_regex_unref ( reg );
    // Throw error if shell parsing fails.
    if ( error != NULL ) {
        char *msg = g_strdup_printf ( "Failed to parse: '%s'\nError: '%s'", string, error->message );
        rofi_view_error_dialog ( msg, FALSE );
        g_free ( msg );
        // print error.
        g_error_free ( error );
        g_free ( res );
        return NULL;
    }
    return res;
}