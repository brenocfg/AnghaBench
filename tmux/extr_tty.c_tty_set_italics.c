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
 int /*<<< orphan*/  TTYC_SITM ; 
 int /*<<< orphan*/  TTYC_SMSO ; 
 int /*<<< orphan*/  global_options ; 
 char* options_get_string (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  tty_putcode (struct tty*,int /*<<< orphan*/ ) ; 
 scalar_t__ tty_term_has (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tty_set_italics(struct tty *tty)
{
	const char	*s;

	if (tty_term_has(tty->term, TTYC_SITM)) {
		s = options_get_string(global_options, "default-terminal");
		if (strcmp(s, "screen") != 0 && strncmp(s, "screen-", 7) != 0) {
			tty_putcode(tty, TTYC_SITM);
			return;
		}
	}
	tty_putcode(tty, TTYC_SMSO);
}