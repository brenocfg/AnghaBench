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
struct TYPE_3__ {int /*<<< orphan*/ * id; } ;
typedef  TYPE_1__ scrollbar_T ;

/* Variables and functions */
 int /*<<< orphan*/  gtk_widget_hide (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_window_manager_hints (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
gui_mch_enable_scrollbar(scrollbar_T *sb, int flag)
{
    if (sb->id == NULL)
	return;

    if (flag)
	gtk_widget_show(sb->id);
    else
	gtk_widget_hide(sb->id);

    update_window_manager_hints(0, 0);
}