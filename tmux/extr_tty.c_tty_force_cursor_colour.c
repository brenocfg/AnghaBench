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
struct tty {int /*<<< orphan*/  ccolour; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTYC_CR ; 
 int /*<<< orphan*/  TTYC_CS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_putcode (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_putcode_ptr1 (struct tty*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static void
tty_force_cursor_colour(struct tty *tty, const char *ccolour)
{
	if (*ccolour == '\0')
		tty_putcode(tty, TTYC_CR);
	else
		tty_putcode_ptr1(tty, TTYC_CS, ccolour);
	free(tty->ccolour);
	tty->ccolour = xstrdup(ccolour);
}