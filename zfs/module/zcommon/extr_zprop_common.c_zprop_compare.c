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
struct TYPE_2__ {scalar_t__ pd_attr; int /*<<< orphan*/  pd_name; } ;
typedef  TYPE_1__ zprop_desc_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ PROP_READONLY ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zprop_compare(const void *arg1, const void *arg2)
{
	const zprop_desc_t *p1 = *((zprop_desc_t **)arg1);
	const zprop_desc_t *p2 = *((zprop_desc_t **)arg2);
	boolean_t p1ro, p2ro;

	p1ro = (p1->pd_attr == PROP_READONLY);
	p2ro = (p2->pd_attr == PROP_READONLY);

	if (p1ro == p2ro)
		return (strcmp(p1->pd_name, p2->pd_name));

	return (p1ro ? -1 : 1);
}