#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  str ;
struct TYPE_10__ {int command; int /*<<< orphan*/  list; int /*<<< orphan*/ ** txt; } ;
typedef  TYPE_2__ loc_cmd ;
struct TYPE_12__ {TYPE_1__* table; } ;
struct TYPE_11__ {int /*<<< orphan*/  list; } ;
struct TYPE_9__ {void* data; } ;

/* Variables and functions */
 int ARRAYSIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  free_loc_cmd (TYPE_2__*) ; 
 size_t htab_hash (char*,TYPE_4__*) ; 
 TYPE_4__ htab_loc ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 TYPE_3__* loc_dlg ; 
 int /*<<< orphan*/  safe_strcpy (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uprintf (char*) ; 

void add_dialog_command(int index, loc_cmd* lcmd)
{
	char str[128];
	loc_cmd* htab_lcmd;
	uint32_t i;
	if ((lcmd == NULL) || (lcmd->txt[0] == NULL) || (index < 0) || (index >= ARRAYSIZE(loc_dlg))) {
		uprintf("localization: invalid parameter for add_dialog_command\n");
		return;
	}

	// A dialog command must be unique, so we use a hash to identify any
	// command that may already have been populated, and ensure it is replaced
	// with the new one.
	// Two dialogs may have different "m IDC_CONTROL" lines, and also
	// "m IDC_CONTROL" and "t IDC_CONTROL" are separate, so we compute two more
	// unique identifiers for dialog and command at the beginning of our string
	str[0] = index + 0x30;
	str[1] = lcmd->command + 0x30;
	safe_strcpy(&str[2], sizeof(str)-2, lcmd->txt[0]);
	i = htab_hash(str, &htab_loc);
	if (i != 0) {
		htab_lcmd = (loc_cmd*)(htab_loc.table[i].data);
		if (htab_lcmd != NULL) {
			list_del(&(htab_lcmd->list));
			free_loc_cmd(htab_lcmd);
		}
		htab_loc.table[i].data = (void*)lcmd;
	}
	list_add(&lcmd->list, &loc_dlg[index].list);
}