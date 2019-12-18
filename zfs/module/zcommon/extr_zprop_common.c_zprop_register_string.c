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
typedef  int /*<<< orphan*/  zprop_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  PROP_TYPE_STRING ; 
 int /*<<< orphan*/  zprop_register_impl (int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
zprop_register_string(int prop, const char *name, const char *def,
    zprop_attr_t attr, int objset_types, const char *values,
    const char *colname)
{
	zprop_register_impl(prop, name, PROP_TYPE_STRING, 0, def, attr,
	    objset_types, values, colname, B_FALSE, B_TRUE, NULL);

}