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
typedef  int /*<<< orphan*/  zpool_handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  cb_any_successful; int /*<<< orphan*/  cb_value; int /*<<< orphan*/  cb_propname; } ;
typedef  TYPE_1__ set_cbdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int zpool_set_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
set_callback(zpool_handle_t *zhp, void *data)
{
	int error;
	set_cbdata_t *cb = (set_cbdata_t *)data;

	error = zpool_set_prop(zhp, cb->cb_propname, cb->cb_value);

	if (!error)
		cb->cb_any_successful = B_TRUE;

	return (error);
}