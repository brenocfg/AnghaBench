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
union options_value {int /*<<< orphan*/ * cmdlist; int /*<<< orphan*/  string; } ;
struct options_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ OPTIONS_IS_COMMAND (struct options_entry*) ; 
 scalar_t__ OPTIONS_IS_STRING (struct options_entry*) ; 
 int /*<<< orphan*/  cmd_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
options_value_free(struct options_entry *o, union options_value *ov)
{
	if (OPTIONS_IS_STRING(o))
		free(ov->string);
	if (OPTIONS_IS_COMMAND(o) && ov->cmdlist != NULL)
		cmd_list_free(ov->cmdlist);
}