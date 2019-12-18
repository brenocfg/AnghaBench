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
struct options_table_entry {char** choices; int /*<<< orphan*/  name; } ;
struct options {int dummy; } ;
struct cmdq_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,char const*) ; 
 int options_get_number (struct options*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  options_set_number (struct options*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int
cmd_set_option_choice(struct cmdq_item *item,
    const struct options_table_entry *oe, struct options *oo,
    const char *value)
{
	const char	**cp;
	int		  n, choice = -1;

	if (value == NULL) {
		choice = options_get_number(oo, oe->name);
		if (choice < 2)
			choice = !choice;
	} else {
		n = 0;
		for (cp = oe->choices; *cp != NULL; cp++) {
			if (strcmp(*cp, value) == 0)
				choice = n;
			n++;
		}
		if (choice == -1) {
			cmdq_error(item, "unknown value: %s", value);
			return (-1);
		}
	}
	options_set_number(oo, oe->name, choice);
	return (0);
}