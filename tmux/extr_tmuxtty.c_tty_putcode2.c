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
typedef  enum tty_code_code { ____Placeholder_tty_code_code } tty_code_code ;

/* Variables and functions */
 int /*<<< orphan*/  tty_puts (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_term_string2 (int /*<<< orphan*/ ,int,int,int) ; 

void
tty_putcode2(struct tty *tty, enum tty_code_code code, int a, int b)
{
	if (a < 0 || b < 0)
		return;
	tty_puts(tty, tty_term_string2(tty->term, code, a, b));
}