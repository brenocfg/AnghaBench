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
 int /*<<< orphan*/  FRAMEBUFFER_SIZE ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  MmUnmapIoSpace (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pScreenBufferHercules ; 

void ConsoleShutdownHercules(void)
{
    ENTER_FUNC();

	// HERC video off
	outb_p(0,0x3b8);
	outb_p(0,0x3bf);

	if(pScreenBufferHercules)
		MmUnmapIoSpace(pScreenBufferHercules,FRAMEBUFFER_SIZE);

    LEAVE_FUNC();
}