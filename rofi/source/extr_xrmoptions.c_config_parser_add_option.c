#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int XrmOptionType ;
typedef  int /*<<< orphan*/  XrmOption ;
struct TYPE_5__ {void** pointer; } ;
struct TYPE_6__ {int type; char const* name; char const* comment; char* mem; int /*<<< orphan*/  source; TYPE_1__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DEFAULT ; 
 TYPE_2__* extra_options ; 
 TYPE_2__* g_realloc (TYPE_2__*,int) ; 
 int num_extra_options ; 
#define  xrm_String 128 

void config_parser_add_option ( XrmOptionType type, const char *key, void **value, const char *comment )
{
    extra_options = g_realloc ( extra_options, ( num_extra_options + 1 ) * sizeof ( XrmOption ) );

    extra_options[num_extra_options].type          = type;
    extra_options[num_extra_options].name          = key;
    extra_options[num_extra_options].value.pointer = value;
    extra_options[num_extra_options].comment       = comment;
    extra_options[num_extra_options].source        = CONFIG_DEFAULT;
    switch ( type )
    {
    case xrm_String:
        extra_options[num_extra_options].mem = ( (char *) ( *value ) );
        break;
    default:
        extra_options[num_extra_options].mem = NULL;
        break;
    }

    num_extra_options++;
}