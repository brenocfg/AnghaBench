#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_xrm_database_t ;
typedef  enum ConfigSource { ____Placeholder_ConfigSource } ConfigSource ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_parser_set (TYPE_1__*,char*,int) ; 
 TYPE_1__* extra_options ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup_printf (char*,char const*,int /*<<< orphan*/ ) ; 
 unsigned int num_extra_options ; 
 scalar_t__ xcb_xrm_resource_get_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char**) ; 

__attribute__((used)) static void __config_parse_xresource_options_dynamic ( xcb_xrm_database_t *xDB, enum ConfigSource source )
{
    const char * namePrefix = "rofi";

    for ( unsigned int i = 0; i < num_extra_options; ++i ) {
        char *name;

        name = g_strdup_printf ( "%s.%s", namePrefix, extra_options[i].name );
        char *xrmValue = NULL;
        if ( xcb_xrm_resource_get_string ( xDB, name, NULL, &xrmValue ) == 0 ) {
            config_parser_set ( &( extra_options[i] ), xrmValue, source );
        }
        if ( xrmValue ) {
            free ( xrmValue );
        }

        g_free ( name );
    }
}