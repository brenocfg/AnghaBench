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
typedef  scalar_t__ u_int ;
struct tty {scalar_t__ cx; scalar_t__ sx; scalar_t__ cy; } ;

/* Variables and functions */
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  tty_add (struct tty*,void const*,size_t) ; 

void
tty_putn(struct tty *tty, const void *buf, size_t len, u_int width)
{
	tty_add(tty, buf, len);
	if (tty->cx + width > tty->sx) {
		tty->cx = (tty->cx + width) - tty->sx;
		if (tty->cx <= tty->sx)
			tty->cy++;
		else
			tty->cx = tty->cy = UINT_MAX;
	} else
		tty->cx += width;
}