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
typedef  int /*<<< orphan*/  u_int ;
struct tty {int /*<<< orphan*/  term; } ;
typedef  enum tty_code_code { ____Placeholder_tty_code_code } tty_code_code ;

/* Variables and functions */
 int /*<<< orphan*/  tty_putcode (struct tty*,int) ; 
 int /*<<< orphan*/  tty_putcode1 (struct tty*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ tty_term_has (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
tty_emulate_repeat(struct tty *tty, enum tty_code_code code,
    enum tty_code_code code1, u_int n)
{
	if (tty_term_has(tty->term, code))
		tty_putcode1(tty, code, n);
	else {
		while (n-- > 0)
			tty_putcode(tty, code1);
	}
}