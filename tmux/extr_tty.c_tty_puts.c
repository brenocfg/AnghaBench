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
struct tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  tty_add (struct tty*,char const*,int /*<<< orphan*/ ) ; 

void
tty_puts(struct tty *tty, const char *s)
{
	if (*s != '\0')
		tty_add(tty, s, strlen(s));
}