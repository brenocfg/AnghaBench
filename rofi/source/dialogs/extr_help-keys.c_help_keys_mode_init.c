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
typedef  int /*<<< orphan*/  Mode ;
typedef  int /*<<< orphan*/  KeysHelpModePrivateData ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/ * g_malloc0 (int) ; 
 int /*<<< orphan*/  get_apps (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mode_get_private_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mode_set_private_data (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int help_keys_mode_init ( Mode *sw )
{
    if ( mode_get_private_data ( sw ) == NULL ) {
        KeysHelpModePrivateData *pd = g_malloc0 ( sizeof ( *pd ) );
        mode_set_private_data ( sw, (void *) pd );
        get_apps ( pd );
    }
    return TRUE;
}