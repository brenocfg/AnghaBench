#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char** cb_vdev_names; } ;
typedef  TYPE_1__ iostat_cbdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int for_each_pool (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  is_vdev ; 

__attribute__((used)) static int
are_vdevs_in_pool(int argc, char **argv, char *pool_name,
    iostat_cbdata_t *cb)
{
	char **tmp_name;
	int ret = 0;
	int i;
	int pool_count = 0;

	if ((argc == 0) || !*argv)
		return (0);

	if (pool_name)
		pool_count = 1;

	/* Temporarily hijack cb_vdev_names for a second... */
	tmp_name = cb->cb_vdev_names;

	/* Go though our list of prospective vdev names */
	for (i = 0; i < argc; i++) {
		cb->cb_vdev_names = argv + i;

		/* Is this name a vdev in our pools? */
		ret = for_each_pool(pool_count, &pool_name, B_TRUE, NULL,
		    is_vdev, cb);
		if (!ret) {
			/* No match */
			break;
		}
	}

	cb->cb_vdev_names = tmp_name;

	return (ret);
}