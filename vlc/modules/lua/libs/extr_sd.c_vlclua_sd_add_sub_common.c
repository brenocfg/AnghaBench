#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  services_discovery_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  services_discovery_AddSubItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_sd_add_sub_common( services_discovery_t *p_sd,
                                     input_item_t **pp_node,
                                     input_item_t *p_input )
{
    if( *pp_node != NULL && p_input != NULL )
        services_discovery_AddSubItem( p_sd, *pp_node, p_input );
    return 1;
}