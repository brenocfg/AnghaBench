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
typedef  int /*<<< orphan*/  addons_manager_t ;
typedef  int /*<<< orphan*/  addon_uuid_t ;
typedef  int /*<<< orphan*/  addon_entry_t ;

/* Variables and functions */
 int InstallEntry (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  addon_entry_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getHeldEntryByUUID (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 

int addons_manager_Install( addons_manager_t *p_manager, const addon_uuid_t uuid )
{
    addon_entry_t *p_install_entry = getHeldEntryByUUID( p_manager, uuid );
    if ( ! p_install_entry ) return VLC_EGENERIC;
    int i_ret = InstallEntry( p_manager, p_install_entry );
    addon_entry_Release( p_install_entry );
    return i_ret;
}