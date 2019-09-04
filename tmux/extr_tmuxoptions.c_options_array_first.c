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
struct options_array_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPTIONS_IS_ARRAY (struct options_entry*) ; 
 struct options_array_item* RB_MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  options_array ; 

struct options_array_item *
options_array_first(struct options_entry *o)
{
	if (!OPTIONS_IS_ARRAY(o))
		return (NULL);
	return (RB_MIN(options_array, &o->value.array));
}