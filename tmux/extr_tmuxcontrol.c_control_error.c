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
struct cmdq_item {struct client* client; } ;
struct client {int dummy; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_NORMAL ; 
 int /*<<< orphan*/  cmdq_guard (struct cmdq_item*,char*,int) ; 
 int /*<<< orphan*/  control_write (struct client*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static enum cmd_retval
control_error(struct cmdq_item *item, void *data)
{
	struct client	*c = item->client;
	char		*error = data;

	cmdq_guard(item, "begin", 1);
	control_write(c, "parse error: %s", error);
	cmdq_guard(item, "error", 1);

	free(error);
	return (CMD_RETURN_NORMAL);
}