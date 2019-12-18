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
struct TYPE_2__ {scalar_t__ cb_guid; int /*<<< orphan*/ * cb_zhp; } ;
typedef  TYPE_1__ find_cbdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZPOOL_PROP_GUID ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_get_prop_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
find_pool(zpool_handle_t *zhp, void *data)
{
	find_cbdata_t *cbp = data;

	if (cbp->cb_guid ==
	    zpool_get_prop_int(zhp, ZPOOL_PROP_GUID, NULL)) {
		cbp->cb_zhp = zhp;
		return (1);
	}

	zpool_close(zhp);
	return (0);
}