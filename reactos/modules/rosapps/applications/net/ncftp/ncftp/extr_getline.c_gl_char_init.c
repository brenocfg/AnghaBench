#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int t_intrc; int t_quitc; int t_suspc; int t_dsuspc; int sg_flags; int* c_cc; int c_iflag; int c_lflag; } ;
struct TYPE_12__ {int* c_cc; int c_iflag; int c_lflag; } ;

/* Variables and functions */
 int BRKINT ; 
 int ECHO ; 
 int ICANON ; 
 int IEXTEN ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int ISIG ; 
 int ISTRIP ; 
 int IXOFF ; 
 int IXON ; 
 int RAW ; 
 int /*<<< orphan*/  TCGETA ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  TCSETA ; 
 int /*<<< orphan*/  TIOCGETC ; 
 int /*<<< orphan*/  TIOCGETP ; 
 int /*<<< orphan*/  TIOCGLTC ; 
 int /*<<< orphan*/  TIOCSETN ; 
 size_t VDSUSP ; 
 size_t VINTR ; 
 size_t VMIN ; 
 size_t VQUIT ; 
 size_t VSUSP ; 
 size_t VTIME ; 
 int gl_dsuspc ; 
 int gl_intrc ; 
 int gl_quitc ; 
 int gl_suspc ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__ ltch ; 
 TYPE_2__ new_termio ; 
 TYPE_1__ new_termios ; 
 TYPE_2__ new_tty ; 
 TYPE_2__ old_termio ; 
 TYPE_1__ old_termios ; 
 TYPE_2__ old_tty ; 
 scalar_t__ tcgetattr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_2__ tch ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

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