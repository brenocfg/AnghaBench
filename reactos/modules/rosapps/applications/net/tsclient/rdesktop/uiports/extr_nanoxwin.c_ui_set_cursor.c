#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  GR_CURSOR_ID ;

/* Variables and functions */
 int /*<<< orphan*/  GrSetWindowCursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_wnd ; 

void ui_set_cursor(void * cursor)
{
  GrSetWindowCursor(g_wnd, (GR_CURSOR_ID)cursor);
}