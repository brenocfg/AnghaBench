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
struct tty {scalar_t__ sx; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_margin (struct tty*,int /*<<< orphan*/ ,scalar_t__) ; 

void
tty_margin_off(struct tty *tty)
{
	tty_margin(tty, 0, tty->sx - 1);
}