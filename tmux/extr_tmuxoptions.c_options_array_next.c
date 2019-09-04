#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct options_array_item {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  array; } ;
struct TYPE_4__ {TYPE_1__ value; } ;

/* Variables and functions */
 struct options_array_item* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct options_array_item*) ; 
 TYPE_2__* o ; 
 int /*<<< orphan*/  options_array ; 

struct options_array_item *
options_array_next(struct options_array_item *a)
{
	return (RB_NEXT(options_array, &o->value.array, a));
}