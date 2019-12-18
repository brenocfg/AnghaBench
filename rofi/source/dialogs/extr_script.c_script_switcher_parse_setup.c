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
struct TYPE_5__ {int /*<<< orphan*/  _get_display_value; int /*<<< orphan*/ * _preprocess_input; int /*<<< orphan*/ * _get_completion; int /*<<< orphan*/  _get_icon; int /*<<< orphan*/  _get_message; int /*<<< orphan*/  _token_match; int /*<<< orphan*/  _destroy; int /*<<< orphan*/  _result; int /*<<< orphan*/  _get_num_entries; int /*<<< orphan*/  _init; int /*<<< orphan*/  (* free ) (TYPE_1__*) ;void* ed; void* name; } ;
typedef  TYPE_1__ Mode ;

/* Variables and functions */
 int /*<<< orphan*/  _get_display_value ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 TYPE_1__* g_malloc0 (int) ; 
 void* g_strdup (char const*) ; 
 scalar_t__ rofi_expand_path (char*) ; 
 int /*<<< orphan*/  script_get_icon ; 
 int /*<<< orphan*/  script_get_message ; 
 int /*<<< orphan*/  script_mode_destroy ; 
 int /*<<< orphan*/  script_mode_get_num_entries ; 
 int /*<<< orphan*/  script_mode_init ; 
 int /*<<< orphan*/  script_mode_result ; 
 int /*<<< orphan*/  script_switcher_free (TYPE_1__*) ; 
 int /*<<< orphan*/  script_token_match ; 
 int /*<<< orphan*/  stderr ; 
 char* strtok_r (char*,char const* const,char**) ; 

Mode *script_switcher_parse_setup ( const char *str )
{
    Mode              *sw    = g_malloc0 ( sizeof ( *sw ) );
    char              *endp  = NULL;
    char              *parse = g_strdup ( str );
    unsigned int      index  = 0;
    const char *const sep    = ":";
    for ( char *token = strtok_r ( parse, sep, &endp ); token != NULL; token = strtok_r ( NULL, sep, &endp ) ) {
        if ( index == 0 ) {
            sw->name = g_strdup ( token );
        }
        else if ( index == 1 ) {
            sw->ed = (void *) rofi_expand_path ( token );
        }
        index++;
    }
    g_free ( parse );
    if ( index == 2 ) {
        sw->free               = script_switcher_free;
        sw->_init              = script_mode_init;
        sw->_get_num_entries   = script_mode_get_num_entries;
        sw->_result            = script_mode_result;
        sw->_destroy           = script_mode_destroy;
        sw->_token_match       = script_token_match;
        sw->_get_message       = script_get_message;
        sw->_get_icon          = script_get_icon;
        sw->_get_completion    = NULL,
        sw->_preprocess_input  = NULL,
        sw->_get_display_value = _get_display_value;

        return sw;
    }
    fprintf ( stderr, "The script command '%s' has %u options, but needs 2: <name>:<script>.", str, index );
    script_switcher_free ( sw );
    return NULL;
}