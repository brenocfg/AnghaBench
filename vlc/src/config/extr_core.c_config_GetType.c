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
struct TYPE_3__ {int /*<<< orphan*/  i_type; } ;
typedef  TYPE_1__ module_config_t ;

/* Variables and functions */
 int CONFIG_CLASS (int /*<<< orphan*/ ) ; 
#define  CONFIG_ITEM_BOOL 131 
#define  CONFIG_ITEM_FLOAT 130 
#define  CONFIG_ITEM_INTEGER 129 
#define  CONFIG_ITEM_STRING 128 
 int VLC_VAR_BOOL ; 
 int VLC_VAR_FLOAT ; 
 int VLC_VAR_INTEGER ; 
 int VLC_VAR_STRING ; 
 TYPE_1__* config_FindConfig (char const*) ; 

int config_GetType(const char *psz_name)
{
    module_config_t *p_config = config_FindConfig(psz_name);

    /* sanity checks */
    if( !p_config )
    {
        return 0;
    }

    switch( CONFIG_CLASS(p_config->i_type) )
    {
        case CONFIG_ITEM_FLOAT:
            return VLC_VAR_FLOAT;
        case CONFIG_ITEM_INTEGER:
            return VLC_VAR_INTEGER;
        case CONFIG_ITEM_BOOL:
            return VLC_VAR_BOOL;
        case CONFIG_ITEM_STRING:
            return VLC_VAR_STRING;
        default:
            return 0;
    }
}