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
struct cmd_list {int references; int /*<<< orphan*/  list; scalar_t__ group; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmd_list_next_group ; 
 struct cmd_list* xcalloc (int,int) ; 

struct cmd_list *
cmd_list_new(void)
{
	struct cmd_list	*cmdlist;

	cmdlist = xcalloc(1, sizeof *cmdlist);
	cmdlist->references = 1;
	cmdlist->group = cmd_list_next_group++;
	TAILQ_INIT(&cmdlist->list);
	return (cmdlist);
}