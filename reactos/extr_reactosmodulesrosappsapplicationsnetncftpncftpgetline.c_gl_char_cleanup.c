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
 int /*<<< orphan*/  TCSETA ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  old_termio ; 

__attribute__((used)) static void
gl_char_cleanup(void)		/* undo effects of gl_char_init */
{
#ifdef __unix__
#	ifdef HAVE_TERMIOS_H
		tcsetattr(0, TCSANOW, &old_termios);
#	elif defined(TIOCSETN)		/* BSD */
		ioctl(0, TIOCSETN, &old_tty);
#	else			/* SYSV */
		ioctl(0, TCSETA, &old_termio);
#	endif
#endif /* __unix__ */
}