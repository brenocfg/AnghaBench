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
 int /*<<< orphan*/  FlushConsoleInputBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  gl_char_cleanup () ; 
 scalar_t__ gl_init_done ; 

__attribute__((used)) static void
gl_cleanup(void)
/* undo effects of gl_init, as necessary */
{
    if (gl_init_done > 0)
        gl_char_cleanup();
    gl_init_done = 0;
#ifdef __windows__
	Sleep(40);
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
#endif
}