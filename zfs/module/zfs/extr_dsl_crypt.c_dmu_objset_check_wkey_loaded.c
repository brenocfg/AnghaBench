#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsl_wrapping_key_t ;
struct TYPE_6__ {TYPE_1__* dd_pool; } ;
typedef  TYPE_2__ dsl_dir_t ;
struct TYPE_5__ {int /*<<< orphan*/  dp_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_wrapping_key_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spa_keystore_wkey_hold_dd (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
dmu_objset_check_wkey_loaded(dsl_dir_t *dd)
{
	int ret;
	dsl_wrapping_key_t *wkey = NULL;

	ret = spa_keystore_wkey_hold_dd(dd->dd_pool->dp_spa, dd, FTAG,
	    &wkey);
	if (ret != 0)
		return (SET_ERROR(EACCES));

	dsl_wrapping_key_rele(wkey, FTAG);

	return (0);
}