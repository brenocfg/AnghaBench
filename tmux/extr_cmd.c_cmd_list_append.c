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
struct cmd_list {int /*<<< orphan*/  list; int /*<<< orphan*/  group; } ;
struct cmd {int /*<<< orphan*/  group; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qentry ; 

void
cmd_list_append(struct cmd_list *cmdlist, struct cmd *cmd)
{
	cmd->group = cmdlist->group;
	TAILQ_INSERT_TAIL(&cmdlist->list, cmd, qentry);
}