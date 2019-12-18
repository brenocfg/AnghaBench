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
struct TYPE_4__ {int* num; int* snum; char** str; int* charc; } ;
struct TYPE_5__ {int type; scalar_t__ source; char* name; TYPE_1__ value; } ;
typedef  TYPE_2__ XrmOption ;

/* Variables and functions */
 scalar_t__ CONFIG_DEFAULT ; 
 int TRUE ; 
 int /*<<< orphan*/  printf (char*,...) ; 
#define  xrm_Boolean 132 
#define  xrm_Char 131 
#define  xrm_Number 130 
#define  xrm_SNumber 129 
#define  xrm_String 128 

__attribute__((used)) static void config_parse_dump_config_option ( XrmOption *option )
{
    if ( option->type == xrm_Char || option->source == CONFIG_DEFAULT ) {
        printf ( "/*" );
    }
    printf ( "\t%s: ", option->name );
    switch ( option->type )
    {
    case xrm_Number:
        printf ( "%u", *( option->value.num ) );
        break;
    case xrm_SNumber:
        printf ( "%i", *( option->value.snum ) );
        break;
    case xrm_String:
        if ( ( *( option->value.str ) ) != NULL ) {
            // TODO should this be escaped?
            printf ( "\"%s\"", *( option->value.str ) );
        }
        break;
    case xrm_Boolean:
        printf ( "%s", ( *( option->value.num ) == TRUE ) ? "true" : "false" );
        break;
    case xrm_Char:
        // TODO
        if ( *( option->value.charc ) > 32 && *( option->value.charc ) < 127 ) {
            printf ( "'%c'", *( option->value.charc ) );
        }
        else {
            printf ( "'\\x%02X'", *( option->value.charc ) );
        }
        printf ( " /* unsupported */" );
        break;
    default:
        break;
    }

    printf ( ";" );
    if ( option->type == xrm_Char || option->source == CONFIG_DEFAULT ) {
        printf ( "*/" );
    }
    printf ( "\n" );
}