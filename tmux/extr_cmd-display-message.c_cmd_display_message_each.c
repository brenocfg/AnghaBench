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
struct cmdq_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmdq_print (struct cmdq_item*,char*,char const*,char const*) ; 

__attribute__((used)) static void
cmd_display_message_each(const char *key, const char *value, void *arg)
{
	struct cmdq_item	*item = arg;

	cmdq_print(item, "%s=%s", key, value);
}