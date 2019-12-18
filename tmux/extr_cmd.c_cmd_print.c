#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cmd {TYPE_1__* entry; int /*<<< orphan*/  args; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 char* args_print (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int /*<<< orphan*/ ,char*) ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 

char *
cmd_print(struct cmd *cmd)
{
	char	*out, *s;

	s = args_print(cmd->args);
	if (*s != '\0')
		xasprintf(&out, "%s %s", cmd->entry->name, s);
	else
		out = xstrdup(cmd->entry->name);
	free(s);

	return (out);
}