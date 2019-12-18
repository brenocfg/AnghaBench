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
struct TYPE_3__ {scalar_t__ ctrl_id; int /*<<< orphan*/ ** txt; } ;
typedef  TYPE_1__ loc_cmd ;

/* Variables and functions */
 scalar_t__ MSG_000 ; 
 scalar_t__ MSG_MAX ; 
 int /*<<< orphan*/ ** msg_table ; 
 int /*<<< orphan*/  safe_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uprintf (char*) ; 

void add_message_command(loc_cmd* lcmd)
{
	if (lcmd == NULL) {
		uprintf("localization: invalid parameter for add_message_command\n");
		return;
	}

	if ((lcmd->ctrl_id <= MSG_000) || (lcmd->ctrl_id >= MSG_MAX)) {
		uprintf("localization: invalid MSG_ index\n");
		return;
	}

	safe_free(msg_table[lcmd->ctrl_id-MSG_000]);
	msg_table[lcmd->ctrl_id-MSG_000] = lcmd->txt[1];
	lcmd->txt[1] = NULL;	// String would be freed after this call otherwise
}