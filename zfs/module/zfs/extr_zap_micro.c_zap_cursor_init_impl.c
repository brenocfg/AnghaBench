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
struct TYPE_3__ {int /*<<< orphan*/  zc_prefetch; scalar_t__ zc_cd; scalar_t__ zc_hash; void* zc_serialized; void* zc_zapobj; int /*<<< orphan*/ * zc_leaf; int /*<<< orphan*/ * zc_zap; int /*<<< orphan*/ * zc_objset; } ;
typedef  TYPE_1__ zap_cursor_t ;
typedef  void* uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */

__attribute__((used)) static void
zap_cursor_init_impl(zap_cursor_t *zc, objset_t *os, uint64_t zapobj,
    uint64_t serialized, boolean_t prefetch)
{
	zc->zc_objset = os;
	zc->zc_zap = NULL;
	zc->zc_leaf = NULL;
	zc->zc_zapobj = zapobj;
	zc->zc_serialized = serialized;
	zc->zc_hash = 0;
	zc->zc_cd = 0;
	zc->zc_prefetch = prefetch;
}