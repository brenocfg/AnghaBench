#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* c_cc; int c_iflag; int c_lflag; } ;

/* Variables and functions */
 int BRKINT ; 
 int ECHO ; 
 int ICANON ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int ISIG ; 
 int ISTRIP ; 
 int IXOFF ; 
 int IXON ; 
 int /*<<< orphan*/  TCGETA ; 
 int /*<<< orphan*/  TCSETA ; 
 size_t VINTR ; 
 size_t VMIN ; 
 size_t VQUIT ; 
 size_t VTIME ; 
 int gl_intrc ; 
 int gl_quitc ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__ new_termio ; 
 TYPE_1__ old_termio ; 

__attribute__((used)) static void
gl_char_init(void)			/* turn off input echo */
{
#ifdef __unix__
#	ifdef HAVE_TERMIOS_H		/* Use POSIX */
		if (tcgetattr(0, &old_termios) == 0) {
			gl_intrc = old_termios.c_cc[VINTR];
			gl_quitc = old_termios.c_cc[VQUIT];
#		ifdef VSUSP
			gl_suspc = old_termios.c_cc[VSUSP];
#		endif
#		ifdef VDSUSP
			gl_dsuspc = old_termios.c_cc[VDSUSP];
#		endif
		}
		new_termios = old_termios;
		new_termios.c_iflag &= ~(BRKINT|ISTRIP|IXON|IXOFF);
		new_termios.c_iflag |= (IGNBRK|IGNPAR);
		new_termios.c_lflag &= ~(ICANON|ISIG|IEXTEN|ECHO);
		new_termios.c_cc[VMIN] = 1;
		new_termios.c_cc[VTIME] = 0;
		tcsetattr(0, TCSANOW, &new_termios);
#	elif defined(TIOCSETN)		/* BSD */
		if (ioctl(0, TIOCGETC, &tch) == 0) {
			gl_intrc = tch.t_intrc;
			gl_quitc = tch.t_quitc;
		}
		ioctl(0, TIOCGLTC, &ltch);
		gl_suspc = ltch.t_suspc;
		gl_dsuspc = ltch.t_dsuspc;
		ioctl(0, TIOCGETP, &old_tty);
		new_tty = old_tty;
		new_tty.sg_flags |= RAW;
		new_tty.sg_flags &= ~ECHO;
		ioctl(0, TIOCSETN, &new_tty);
#	else				/* SYSV */
		if (ioctl(0, TCGETA, &old_termio) == 0) {
			gl_intrc = old_termio.c_cc[VINTR];
			gl_quitc = old_termio.c_cc[VQUIT];
		}
		new_termio = old_termio;
		new_termio.c_iflag &= ~(BRKINT|ISTRIP|IXON|IXOFF);
		new_termio.c_iflag |= (IGNBRK|IGNPAR);
		new_termio.c_lflag &= ~(ICANON|ISIG|ECHO);
		new_termio.c_cc[VMIN] = 1;
		new_termio.c_cc[VTIME] = 0;
		ioctl(0, TCSETA, &new_termio);
#	endif
#endif /* __unix__ */
}