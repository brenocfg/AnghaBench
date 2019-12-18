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
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int dmu_objset_hold_flags (char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ **) ; 

int
dmu_objset_hold(const char *name, void *tag, objset_t **osp)
{
	return (dmu_objset_hold_flags(name, B_FALSE, tag, osp));
}