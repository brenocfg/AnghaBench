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
 int /*<<< orphan*/  MB_OK ; 
 int /*<<< orphan*/  MessageBeep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_putc (char) ; 

__attribute__((used)) static void
gl_beep(void)
{
#ifdef __windows__
	MessageBeep(MB_OK);
#else
	gl_putc('\007');
#endif
}