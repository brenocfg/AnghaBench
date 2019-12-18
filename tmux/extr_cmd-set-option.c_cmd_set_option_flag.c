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
struct options_table_entry {int /*<<< orphan*/  name; } ;
struct options {int dummy; } ;
struct cmdq_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,char const*) ; 
 int /*<<< orphan*/  options_get_number (struct options*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  options_set_number (struct options*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
cmd_set_option_flag(struct cmdq_item *item,
    const struct options_table_entry *oe, struct options *oo,
    const char *value)
{
	int	flag;

	if (value == NULL || *value == '\0')
		flag = !options_get_number(oo, oe->name);
	else if (strcmp(value, "1") == 0 ||
	    strcasecmp(value, "on") == 0 ||
	    strcasecmp(value, "yes") == 0)
		flag = 1;
	else if (strcmp(value, "0") == 0 ||
	    strcasecmp(value, "off") == 0 ||
	    strcasecmp(value, "no") == 0)
		flag = 0;
	else {
		cmdq_error(item, "bad value: %s", value);
		return (-1);
	}
	options_set_number(oo, oe->name, flag);
	return (0);
}