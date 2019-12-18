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
struct options_array_item {scalar_t__ index; } ;

/* Variables and functions */

__attribute__((used)) static int
options_array_cmp(struct options_array_item *a1, struct options_array_item *a2)
{
	if (a1->index < a2->index)
		return (-1);
	if (a1->index > a2->index)
		return (1);
	return (0);
}