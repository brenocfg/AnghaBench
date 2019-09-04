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
typedef  int /*<<< orphan*/  u_char ;
struct args_entry {int /*<<< orphan*/  flag; } ;
struct args {int /*<<< orphan*/  tree; } ;

/* Variables and functions */
 struct args_entry* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct args_entry*) ; 
 int /*<<< orphan*/  args_tree ; 

__attribute__((used)) static struct args_entry *
args_find(struct args *args, u_char ch)
{
	struct args_entry	entry;

	entry.flag = ch;
	return (RB_FIND(args_tree, &args->tree, &entry));
}