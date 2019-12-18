#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hosts_list_length; int /*<<< orphan*/  hosts_list; } ;
typedef  TYPE_1__ SSHModePrivateData ;
typedef  int /*<<< orphan*/  Mode ;

/* Variables and functions */
 int TRUE ; 
 TYPE_1__* g_malloc0 (int) ; 
 int /*<<< orphan*/  get_ssh (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mode_get_private_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mode_set_private_data (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int ssh_mode_init ( Mode *sw )
{
    if ( mode_get_private_data ( sw ) == NULL ) {
        SSHModePrivateData *pd = g_malloc0 ( sizeof ( *pd ) );
        mode_set_private_data ( sw, (void *) pd );
        pd->hosts_list = get_ssh ( pd, &( pd->hosts_list_length ) );
    }
    return TRUE;
}