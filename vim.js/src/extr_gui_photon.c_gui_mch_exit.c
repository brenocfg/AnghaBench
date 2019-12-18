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
struct TYPE_2__ {int /*<<< orphan*/  event_buffer; int /*<<< orphan*/  vimWindow; } ;

/* Variables and functions */
 int /*<<< orphan*/  PtDestroyWidget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PxTranslateSet (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  charset_translate ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  panel_titles ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ ) ; 

void
gui_mch_exit(int rc)
{
    PtDestroyWidget(gui.vimWindow);

    PxTranslateSet(charset_translate, NULL);

    vim_free(gui.event_buffer);

#ifdef USE_PANEL_GROUPS
    vim_free(panel_titles);
#endif
}