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
typedef  int u_int ;
struct tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  tty_putn (struct tty*,char*,int,int) ; 

__attribute__((used)) static void
tty_repeat_space(struct tty *tty, u_int n)
{
	static char s[500];

	if (*s != ' ')
		memset(s, ' ', sizeof s);

	while (n > sizeof s) {
		tty_putn(tty, s, sizeof s, sizeof s);
		n -= sizeof s;
	}
	if (n != 0)
		tty_putn(tty, s, n, n);
}