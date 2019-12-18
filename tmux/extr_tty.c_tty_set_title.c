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
struct tty {int /*<<< orphan*/  term; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTYC_FSL ; 
 int /*<<< orphan*/  TTYC_TSL ; 
 int /*<<< orphan*/  tty_putcode (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_puts (struct tty*,char const*) ; 
 int /*<<< orphan*/  tty_term_has (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
tty_set_title(struct tty *tty, const char *title)
{
	if (!tty_term_has(tty->term, TTYC_TSL) ||
	    !tty_term_has(tty->term, TTYC_FSL))
		return;

	tty_putcode(tty, TTYC_TSL);
	tty_puts(tty, title);
	tty_putcode(tty, TTYC_FSL);
}