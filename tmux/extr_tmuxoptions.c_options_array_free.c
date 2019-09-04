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
struct TYPE_2__ {int /*<<< orphan*/  array; } ;
struct options_entry {TYPE_1__ value; } ;
struct options_array_item {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct options_array_item*) ; 
 int /*<<< orphan*/  free (struct options_array_item*) ; 
 int /*<<< orphan*/  options_array ; 
 int /*<<< orphan*/  options_value_free (struct options_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
options_array_free(struct options_entry *o, struct options_array_item *a)
{
	options_value_free(o, &a->value);
	RB_REMOVE(options_array, &o->value.array, a);
	free(a);
}