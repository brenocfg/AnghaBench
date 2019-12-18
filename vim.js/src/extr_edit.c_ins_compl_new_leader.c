#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  Ctrl_N ; 
 scalar_t__ FAIL ; 
 void* FALSE ; 
 void* TRUE ; 
 scalar_t__ compl_cont_status ; 
 int compl_enter_selects ; 
 scalar_t__ compl_leader ; 
 int /*<<< orphan*/ * compl_match_array ; 
 void* compl_restarting ; 
 scalar_t__ compl_started ; 
 void* compl_used_match ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_update_cursor (void*,void*) ; 
 int /*<<< orphan*/  ins_bytes (scalar_t__) ; 
 int /*<<< orphan*/  ins_compl_del_pum () ; 
 int /*<<< orphan*/  ins_compl_delete () ; 
 scalar_t__ ins_compl_len () ; 
 int /*<<< orphan*/  ins_compl_set_original_text (scalar_t__) ; 
 int /*<<< orphan*/  ins_compl_show_pum () ; 
 scalar_t__ ins_complete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_flush () ; 
 int /*<<< orphan*/  setcursor () ; 
 scalar_t__ spell_bad_len ; 
 int /*<<< orphan*/  update_screen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ins_compl_new_leader()
{
    ins_compl_del_pum();
    ins_compl_delete();
    ins_bytes(compl_leader + ins_compl_len());
    compl_used_match = FALSE;

    if (compl_started)
	ins_compl_set_original_text(compl_leader);
    else
    {
#ifdef FEAT_SPELL
	spell_bad_len = 0;	/* need to redetect bad word */
#endif
	/*
	 * Matches were cleared, need to search for them now.  First display
	 * the changed text before the cursor.  Set "compl_restarting" to
	 * avoid that the first match is inserted.
	 */
	update_screen(0);
#ifdef FEAT_GUI
	if (gui.in_use)
	{
	    /* Show the cursor after the match, not after the redrawn text. */
	    setcursor();
	    out_flush();
	    gui_update_cursor(FALSE, FALSE);
	}
#endif
	compl_restarting = TRUE;
	if (ins_complete(Ctrl_N) == FAIL)
	    compl_cont_status = 0;
	compl_restarting = FALSE;
    }

    compl_enter_selects = !compl_used_match;

    /* Show the popup menu with a different set of matches. */
    ins_compl_show_pum();

    /* Don't let Enter select the original text when there is no popup menu. */
    if (compl_match_array == NULL)
	compl_enter_selects = FALSE;
}