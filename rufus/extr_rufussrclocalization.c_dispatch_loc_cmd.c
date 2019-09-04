#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ command; scalar_t__ ctrl_id; int /*<<< orphan*/ ** txt; } ;
typedef  TYPE_1__ loc_cmd ;
struct TYPE_12__ {scalar_t__ id; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t ARRAYSIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 size_t IDD_DIALOG ; 
#define  LC_BASE 130 
#define  LC_GROUP 129 
#define  LC_TEXT 128 
 scalar_t__ MSG_000 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  add_dialog_command (int,TYPE_1__*) ; 
 int /*<<< orphan*/  add_message_command (TYPE_1__*) ; 
 scalar_t__ atoi (int /*<<< orphan*/ *) ; 
 TYPE_2__* control_id ; 
 scalar_t__ default_msg_table ; 
 int /*<<< orphan*/  free_loc_cmd (TYPE_1__*) ; 
 int /*<<< orphan*/  get_loc_data_file (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* get_locale_from_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* loc_dlg ; 
 int /*<<< orphan*/  luprint (char*) ; 
 int /*<<< orphan*/  luprintf (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ msg_table ; 
 scalar_t__ safe_strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ safe_strncmp (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  uprintf (char*,int /*<<< orphan*/ *) ; 

BOOL dispatch_loc_cmd(loc_cmd* lcmd)
{
	size_t i;
	static int dlg_index = 0;
	loc_cmd* base_locale = NULL;
	const char* msg_prefix = "MSG_";

	if (lcmd == NULL)
		return FALSE;

	if (lcmd->command <= LC_TEXT) {
		// Any command up to LC_TEXT takes a control ID in text[0]
		if (safe_strncmp(lcmd->txt[0], msg_prefix, 4) == 0) {
			// The unneeded NULL check is to silence a VS warning
			if ((lcmd->txt[0] == NULL) || (lcmd->command != LC_TEXT)) {
				luprint("only the [t]ext command can be applied to a message (MSG_###)\n");
				goto err;
			}
			// Try to convert the numeric part of a MSG_#### to a numeric
			lcmd->ctrl_id = MSG_000 + atoi(&(lcmd->txt[0][4]));
			if (lcmd->ctrl_id == MSG_000) {
				// Conversion could not be performed
				luprintf("failed to convert the numeric value in '%'\n", lcmd->txt[0]);
				goto err;
			}
			add_message_command(lcmd);
			free_loc_cmd(lcmd);
			return TRUE;
		}
		for (i=0; i<ARRAYSIZE(control_id); i++) {
			if (safe_strcmp(lcmd->txt[0], control_id[i].name) == 0) {
				lcmd->ctrl_id = control_id[i].id;
				break;
			}
		}
		if (lcmd->ctrl_id < 0) {
			luprintf("unknown control '%s'\n", lcmd->txt[0]);
			goto err;
		}
	}

	// Don't process UI commands when we're dealing with the default
	if (msg_table == default_msg_table) {
		free_loc_cmd(lcmd);
		return TRUE;
	}

	switch(lcmd->command) {
	// NB: For commands that take an ID, ctrl_id is always a valid index at this stage
	case LC_TEXT:
		add_dialog_command(dlg_index, lcmd);
		break;
	case LC_GROUP:
		if ((lcmd->ctrl_id-IDD_DIALOG) > ARRAYSIZE(loc_dlg)) {
			luprintf("'%s' is not a group ID\n", lcmd->txt[0]);
			goto err;
		}
		dlg_index = lcmd->ctrl_id - IDD_DIALOG;
		free_loc_cmd(lcmd);
		break;
	case LC_BASE:
		base_locale = get_locale_from_name(lcmd->txt[0], FALSE);
		if (base_locale != NULL) {
			uprintf("localization: using locale base '%s'\n", lcmd->txt[0]);
			get_loc_data_file(NULL, base_locale);
		} else {
			luprintf("locale base '%s' not found - ignoring", lcmd->txt[0]);
		}
		free_loc_cmd(lcmd);
		break;
	default:
		free_loc_cmd(lcmd);
		break;
	}
	return TRUE;

err:
	free_loc_cmd(lcmd);
	return FALSE;
}