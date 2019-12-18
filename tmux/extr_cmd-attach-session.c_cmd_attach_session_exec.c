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
struct cmd {struct args* args; } ;
struct args {int dummy; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int /*<<< orphan*/  args_get (struct args*,char) ; 
 int /*<<< orphan*/  args_has (struct args*,char) ; 
 int cmd_attach_session (struct cmdq_item*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum cmd_retval
cmd_attach_session_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args	*args = self->args;

	return (cmd_attach_session(item, args_get(args, 't'),
	    args_has(args, 'd'), args_has(args, 'x'), args_has(args, 'r'),
	    args_get(args, 'c'), args_has(args, 'E')));
}