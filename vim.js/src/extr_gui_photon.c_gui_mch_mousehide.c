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
struct TYPE_2__ {int pointer_hidden; int /*<<< orphan*/  vimTextArea; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUI_PH_MOUSE_TYPE ; 
 int MOUSE_SHOW ; 
 int /*<<< orphan*/  Ph_CURSOR_NONE ; 
 int /*<<< orphan*/  PtSetResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pt_ARG_CURSOR_TYPE ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  last_shape ; 
 int /*<<< orphan*/  mch_set_mouse_shape (int /*<<< orphan*/ ) ; 

void
gui_mch_mousehide(int hide)
{
    if (gui.pointer_hidden != hide)
    {
	gui.pointer_hidden = hide;
#ifdef FEAT_MOUSESHAPE
	if (hide)
	    PtSetResource(gui.vimTextArea, Pt_ARG_CURSOR_TYPE,
		    Ph_CURSOR_NONE, 0);
	else
	    mch_set_mouse_shape(last_shape);
#else
	PtSetResource(gui.vimTextArea, Pt_ARG_CURSOR_TYPE,
		(hide == MOUSE_SHOW) ? GUI_PH_MOUSE_TYPE : Ph_CURSOR_NONE,
		0);
#endif
    }
}