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
typedef  enum ConfigSource { ____Placeholder_ConfigSource } ConfigSource ;
struct TYPE_4__ {unsigned int* num; int* snum; int /*<<< orphan*/ * charc; int /*<<< orphan*/ ** str; } ;
struct TYPE_5__ {int type; int source; TYPE_1__ value; int /*<<< orphan*/ * mem; } ;
typedef  TYPE_2__ XrmOption ;

/* Variables and functions */
 unsigned int FALSE ; 
 unsigned int TRUE ; 
 int /*<<< orphan*/  g_ascii_strcasecmp (char*,char*) ; 
 scalar_t__ g_ascii_strtoll (char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ g_ascii_strtoull (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strchomp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strdup (char*) ; 
 int /*<<< orphan*/  helper_parse_char (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
#define  xrm_Boolean 132 
#define  xrm_Char 131 
#define  xrm_Number 130 
#define  xrm_SNumber 129 
#define  xrm_String 128 

__attribute__((used)) static void config_parser_set ( XrmOption *option, char *xrmValue, enum ConfigSource source )
{
    switch ( option->type )
    {
    case xrm_String:
        if ( ( option )->mem != NULL ) {
            g_free ( option->mem );
            option->mem = NULL;
        }
        *( option->value.str ) = g_strchomp ( g_strdup ( xrmValue ) );

        // Memory
        ( option )->mem = *( option->value.str );
        break;
    case xrm_Number:
        *( option->value.num ) = (unsigned int) g_ascii_strtoull ( xrmValue, NULL, 10 );
        break;
    case xrm_SNumber:
        *( option->value.snum ) = (int) g_ascii_strtoll ( xrmValue, NULL, 10 );
        break;
    case xrm_Boolean:
        if ( strlen ( xrmValue ) > 0 &&
             g_ascii_strcasecmp ( xrmValue, "true" ) == 0 ) {
            *( option->value.num ) = TRUE;
        }
        else{
            *( option->value.num ) = FALSE;
        }
        break;
    case xrm_Char:
        *( option->value.charc ) = helper_parse_char ( xrmValue );
        break;
    }
    option->source = source;
}