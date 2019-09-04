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
typedef  int /*<<< orphan*/  rfbCursorPtr ;
typedef  scalar_t__ HCURSOR ;

/* Variables and functions */
 int /*<<< orphan*/  rfbFreeCursor (int /*<<< orphan*/ ) ; 

void
ui_destroy_cursor(HCURSOR cursor)
{
	if (cursor)
		rfbFreeCursor((rfbCursorPtr) cursor);
}