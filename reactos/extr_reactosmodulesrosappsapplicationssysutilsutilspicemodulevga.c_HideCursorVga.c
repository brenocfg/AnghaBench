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

/* Variables and functions */
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  bCursorEnabled ; 
 int inb_p (int) ; 
 int /*<<< orphan*/  outb_p (int,int) ; 

void HideCursorVga(void)
{
    ENTER_FUNC();
	bCursorEnabled=FALSE;

	outb_p(0x0a,0x3d4);
	outb_p(inb_p(0x3d5)|0x20,0x3d5);

    LEAVE_FUNC();
}