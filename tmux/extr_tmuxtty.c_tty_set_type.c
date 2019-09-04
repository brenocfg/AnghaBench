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
struct tty {int term_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_puts (struct tty*,char*) ; 
 scalar_t__ tty_use_margin (struct tty*) ; 

void
tty_set_type(struct tty *tty, int type)
{
	tty->term_type = type;

	if (tty_use_margin(tty))
		tty_puts(tty, "\033[?69h"); /* DECLRMM */
}