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
struct TYPE_3__ {scalar_t__ b_safe; } ;
typedef  TYPE_1__ module_config_t ;

/* Variables and functions */
 TYPE_1__* config_FindConfig (char const*) ; 

bool config_IsSafe( const char *name )
{
    module_config_t *p_config = config_FindConfig( name );
    return p_config != NULL && p_config->b_safe;
}