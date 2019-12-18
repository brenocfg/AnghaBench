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
struct args_entry {int count; } ;
struct args {int dummy; } ;

/* Variables and functions */
 struct args_entry* args_find (struct args*,int /*<<< orphan*/ ) ; 

int
args_has(struct args *args, u_char ch)
{
	struct args_entry	*entry;

	entry = args_find(args, ch);
	if (entry == NULL)
		return (0);
	return (entry->count);
}