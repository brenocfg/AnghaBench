#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  charc; int /*<<< orphan*/ * num; int /*<<< orphan*/  str; int /*<<< orphan*/  snum; } ;
struct TYPE_5__ {int type; char* mem; void* source; TYPE_1__ value; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ XrmOption ;

/* Variables and functions */
 void* CONFIG_CMDLINE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  find_arg (char*) ; 
 int /*<<< orphan*/  find_arg_char (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_arg_int (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_arg_str (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_arg_uint (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup_printf (char*,int /*<<< orphan*/ ) ; 
#define  xrm_Boolean 132 
#define  xrm_Char 131 
#define  xrm_Number 130 
#define  xrm_SNumber 129 
#define  xrm_String 128 

__attribute__((used)) static void config_parse_cmd_option ( XrmOption *option )
{
    // Prepend a - to the option name.
    char *key = g_strdup_printf ( "-%s", option->name );
    switch ( option->type )
    {
    case xrm_Number:
        if ( find_arg_uint ( key, option->value.num ) == TRUE ) {
            option->source = CONFIG_CMDLINE;
        }
        break;
    case xrm_SNumber:
        if ( find_arg_int (  key, option->value.snum ) == TRUE ) {
            option->source = CONFIG_CMDLINE;
        }
        break;
    case xrm_String:
        if ( find_arg_str (  key, option->value.str ) == TRUE ) {
            if ( option->mem != NULL ) {
                g_free ( option->mem );
                option->mem = NULL;
            }
            option->source = CONFIG_CMDLINE;
        }
        break;
    case xrm_Boolean:
        if ( find_arg (  key ) >= 0 ) {
            *( option->value.num ) = TRUE;
            option->source         = CONFIG_CMDLINE;
        }
        else {
            g_free ( key );
            key = g_strdup_printf ( "-no-%s", option->name );
            if ( find_arg (  key ) >= 0 ) {
                *( option->value.num ) = FALSE;
                option->source         = CONFIG_CMDLINE;
            }
        }
        break;
    case xrm_Char:
        if ( find_arg_char (  key, option->value.charc ) == TRUE ) {
            option->source = CONFIG_CMDLINE;
        }
        break;
    default:
        break;
    }
    g_free ( key );
}