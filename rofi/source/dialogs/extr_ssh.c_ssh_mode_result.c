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
struct TYPE_5__ {TYPE_1__* hosts_list; } ;
struct TYPE_4__ {char* hostname; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ SshEntry ;
typedef  TYPE_2__ SSHModePrivateData ;
typedef  int ModeMode ;
typedef  int /*<<< orphan*/  Mode ;

/* Variables and functions */
 int MENU_CUSTOM_INPUT ; 
 int MENU_ENTRY_DELETE ; 
 int MENU_LOWER_MASK ; 
 int MENU_NEXT ; 
 int MENU_OK ; 
 int MENU_PREVIOUS ; 
 int MENU_QUICK_SWITCH ; 
 int MODE_EXIT ; 
 int NEXT_DIALOG ; 
 int PREVIOUS_DIALOG ; 
 int RELOAD_DIALOG ; 
 int /*<<< orphan*/  delete_ssh (char*) ; 
 int /*<<< orphan*/  exec_ssh (TYPE_1__*) ; 
 scalar_t__ mode_get_private_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssh_mode_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssh_mode_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ModeMode ssh_mode_result ( Mode *sw, int mretv, char **input, unsigned int selected_line )
{
    ModeMode           retv  = MODE_EXIT;
    SSHModePrivateData *rmpd = (SSHModePrivateData *) mode_get_private_data ( sw );
    if ( mretv & MENU_NEXT ) {
        retv = NEXT_DIALOG;
    }
    else if ( mretv & MENU_PREVIOUS ) {
        retv = PREVIOUS_DIALOG;
    }
    else if ( mretv & MENU_QUICK_SWITCH ) {
        retv = ( mretv & MENU_LOWER_MASK );
    }
    else if ( ( mretv & MENU_OK ) && rmpd->hosts_list[selected_line].hostname != NULL ) {
        exec_ssh ( &(rmpd->hosts_list[selected_line]) );
    }
    else if ( ( mretv & MENU_CUSTOM_INPUT ) && *input != NULL && *input[0] != '\0' ) {
        SshEntry entry = { .hostname = *input, .port = 0 };
        exec_ssh ( &entry );
    }
    else if ( ( mretv & MENU_ENTRY_DELETE ) && rmpd->hosts_list[selected_line].hostname ) {
        delete_ssh ( rmpd->hosts_list[selected_line].hostname );
        // Stay
        retv = RELOAD_DIALOG;
        ssh_mode_destroy ( sw );
        ssh_mode_init ( sw );
    }
    return retv;
}