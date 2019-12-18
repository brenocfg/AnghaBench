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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPOOL_PROP_AUTOREPLACE ; 
 int /*<<< orphan*/  nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_prop_to_name (int /*<<< orphan*/ ) ; 
 scalar_t__ ztest_random (int) ; 

__attribute__((used)) static nvlist_t *
make_random_props(void)
{
	nvlist_t *props;

	VERIFY0(nvlist_alloc(&props, NV_UNIQUE_NAME, 0));

	if (ztest_random(2) == 0)
		return (props);

	VERIFY0(nvlist_add_uint64(props,
	    zpool_prop_to_name(ZPOOL_PROP_AUTOREPLACE), 1));

	return (props);
}