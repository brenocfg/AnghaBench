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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  fe_hierarchy_t ;

/* Variables and functions */
 int /*<<< orphan*/  HIERARCHY_1 ; 
 int /*<<< orphan*/  HIERARCHY_2 ; 
 int /*<<< orphan*/  HIERARCHY_4 ; 
 int /*<<< orphan*/  HIERARCHY_AUTO ; 
 int /*<<< orphan*/  HIERARCHY_NONE ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 int var_GetInteger (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static fe_hierarchy_t DecodeHierarchy( vlc_object_t *p_access )
{
    fe_hierarchy_t      fe_hierarchy = 0;
    int i_hierarchy = var_GetInteger( p_access, "dvb-hierarchy" );

    msg_Dbg( p_access, "using hierarchy=%d", i_hierarchy );

    switch( i_hierarchy )
    {
        case -1: fe_hierarchy = HIERARCHY_NONE; break;
        case 0: fe_hierarchy = HIERARCHY_AUTO; break;
        case 1: fe_hierarchy = HIERARCHY_1; break;
        case 2: fe_hierarchy = HIERARCHY_2; break;
        case 4: fe_hierarchy = HIERARCHY_4; break;
        default:
            msg_Dbg( p_access, "terrestrial dvb has hierarchy not set, using auto");
            fe_hierarchy = HIERARCHY_AUTO;
            break;
    }
    return fe_hierarchy;
}