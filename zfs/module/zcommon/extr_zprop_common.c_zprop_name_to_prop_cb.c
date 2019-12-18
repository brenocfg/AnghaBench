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
struct TYPE_2__ {int /*<<< orphan*/ * prop_tbl; int /*<<< orphan*/  propname; } ;
typedef  TYPE_1__ name_to_prop_cb_t ;

/* Variables and functions */
 int ZPROP_CONT ; 
 scalar_t__ propname_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zprop_name_to_prop_cb(int prop, void *cb_data)
{
	name_to_prop_cb_t *data = cb_data;

	if (propname_match(data->propname, strlen(data->propname),
	    &data->prop_tbl[prop]))
		return (prop);

	return (ZPROP_CONT);
}