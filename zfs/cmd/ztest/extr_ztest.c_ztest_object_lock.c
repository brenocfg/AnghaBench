#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * zd_object_lock; } ;
typedef  TYPE_1__ ztest_ds_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  rll_t ;
typedef  int /*<<< orphan*/  rl_type_t ;

/* Variables and functions */
 int ZTEST_OBJECT_LOCKS ; 
 int /*<<< orphan*/  ztest_rll_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ztest_object_lock(ztest_ds_t *zd, uint64_t object, rl_type_t type)
{
	rll_t *rll = &zd->zd_object_lock[object & (ZTEST_OBJECT_LOCKS - 1)];

	ztest_rll_lock(rll, type);
}