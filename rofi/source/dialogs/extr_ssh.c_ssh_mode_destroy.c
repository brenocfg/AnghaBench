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
struct TYPE_4__ {unsigned int hosts_list_length; struct TYPE_4__* hosts_list; int /*<<< orphan*/  user_known_hosts; struct TYPE_4__* hostname; } ;
typedef  TYPE_1__ SSHModePrivateData ;
typedef  int /*<<< orphan*/  Mode ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_list_free_full (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (TYPE_1__*)) ; 
 scalar_t__ mode_get_private_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mode_set_private_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ssh_mode_destroy ( Mode *sw )
{
    SSHModePrivateData *rmpd = (SSHModePrivateData *) mode_get_private_data ( sw );
    if ( rmpd != NULL ) {
        for ( unsigned int i = 0; i < rmpd->hosts_list_length; i++ ){
            g_free( rmpd->hosts_list[i].hostname );
        }
        g_list_free_full ( rmpd->user_known_hosts, g_free );
        g_free ( rmpd->hosts_list );
        g_free ( rmpd );
        mode_set_private_data ( sw, NULL );
    }
}