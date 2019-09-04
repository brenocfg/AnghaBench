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
typedef  union options_value {int dummy; } options_value ;
struct options_array_item {union options_value value; } ;

/* Variables and functions */

union options_value *
options_array_item_value(struct options_array_item *a)
{
	return (&a->value);
}