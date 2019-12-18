#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_4__ {void* b_p_iminsert; } ;
struct TYPE_3__ {scalar_t__ in_use; } ;

/* Variables and functions */
 void* B_IMODE_IM ; 
 void* B_IMODE_LMAP ; 
 void* B_IMODE_NONE ; 
 int /*<<< orphan*/  FALSE ; 
 int LANGMAP ; 
 int State ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* curbuf ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_update_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ im_get_status () ; 
 int /*<<< orphan*/  im_set_active (int /*<<< orphan*/ ) ; 
 scalar_t__ map_to_exists_mode (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_iminsert_global () ; 
 int /*<<< orphan*/  showmode () ; 
 int /*<<< orphan*/  status_redraw_curbuf () ; 

__attribute__((used)) static void
ins_ctrl_hat()
{
    if (map_to_exists_mode((char_u *)"", LANGMAP, FALSE))
    {
	/* ":lmap" mappings exists, Toggle use of ":lmap" mappings. */
	if (State & LANGMAP)
	{
	    curbuf->b_p_iminsert = B_IMODE_NONE;
	    State &= ~LANGMAP;
	}
	else
	{
	    curbuf->b_p_iminsert = B_IMODE_LMAP;
	    State |= LANGMAP;
#ifdef USE_IM_CONTROL
	    im_set_active(FALSE);
#endif
	}
    }
#ifdef USE_IM_CONTROL
    else
    {
	/* There are no ":lmap" mappings, toggle IM */
	if (im_get_status())
	{
	    curbuf->b_p_iminsert = B_IMODE_NONE;
	    im_set_active(FALSE);
	}
	else
	{
	    curbuf->b_p_iminsert = B_IMODE_IM;
	    State &= ~LANGMAP;
	    im_set_active(TRUE);
	}
    }
#endif
    set_iminsert_global();
    showmode();
#ifdef FEAT_GUI
    /* may show different cursor shape or color */
    if (gui.in_use)
	gui_update_cursor(TRUE, FALSE);
#endif
#if defined(FEAT_WINDOWS) && defined(FEAT_KEYMAP)
    /* Show/unshow value of 'keymap' in status lines. */
    status_redraw_curbuf();
#endif
}