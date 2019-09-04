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
struct options_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tree; } ;

/* Variables and functions */
 struct options_entry* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct options_entry*) ; 
 TYPE_1__* oo ; 
 int /*<<< orphan*/  options_tree ; 

struct options_entry *
options_next(struct options_entry *o)
{
	return (RB_NEXT(options_tree, &oo->tree, o));
}