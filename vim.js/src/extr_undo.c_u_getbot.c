#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int ue_lcount; int ue_bot; int ue_top; int ue_size; } ;
typedef  TYPE_3__ u_entry_T ;
typedef  int linenr_T ;
struct TYPE_6__ {int ml_line_count; } ;
struct TYPE_9__ {int /*<<< orphan*/  b_u_synced; TYPE_2__* b_u_newhead; TYPE_1__ b_ml; } ;
struct TYPE_7__ {TYPE_3__* uh_getbot_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMSG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_5__* curbuf ; 
 TYPE_3__* u_get_headentry () ; 

__attribute__((used)) static void
u_getbot()
{
    u_entry_T	*uep;
    linenr_T	extra;

    uep = u_get_headentry();	/* check for corrupt undo list */
    if (uep == NULL)
	return;

    uep = curbuf->b_u_newhead->uh_getbot_entry;
    if (uep != NULL)
    {
	/*
	 * the new ue_bot is computed from the number of lines that has been
	 * inserted (0 - deleted) since calling u_save. This is equal to the
	 * old line count subtracted from the current line count.
	 */
	extra = curbuf->b_ml.ml_line_count - uep->ue_lcount;
	uep->ue_bot = uep->ue_top + uep->ue_size + 1 + extra;
	if (uep->ue_bot < 1 || uep->ue_bot > curbuf->b_ml.ml_line_count)
	{
	    EMSG(_("E440: undo line missing"));
	    uep->ue_bot = uep->ue_top + 1;  /* assume all lines deleted, will
					     * get all the old lines back
					     * without deleting the current
					     * ones */
	}

	curbuf->b_u_newhead->uh_getbot_entry = NULL;
    }

    curbuf->b_u_synced = TRUE;
}