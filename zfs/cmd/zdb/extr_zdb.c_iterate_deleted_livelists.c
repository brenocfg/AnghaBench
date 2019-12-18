#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_10__ {int /*<<< orphan*/  za_first_integer; } ;
typedef  TYPE_1__ zap_attribute_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_11__ {int /*<<< orphan*/ * spa_meta_objset; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  (* ll_iter_t ) (TYPE_3__*,void*) ;
struct TYPE_12__ {int /*<<< orphan*/ * dl_os; } ;
typedef  TYPE_3__ dsl_deadlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int) ; 
 int /*<<< orphan*/  DMU_POOL_DELETED_CLONES ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int ENOENT ; 
 int /*<<< orphan*/  dsl_deadlist_close (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_deadlist_open (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int zap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iterate_deleted_livelists(spa_t *spa, ll_iter_t func, void *arg)
{
	objset_t *mos = spa->spa_meta_objset;
	uint64_t zap_obj;
	int err = zap_lookup(mos, DMU_POOL_DIRECTORY_OBJECT,
	    DMU_POOL_DELETED_CLONES, sizeof (uint64_t), 1, &zap_obj);
	if (err == ENOENT)
		return;
	ASSERT0(err);

	zap_cursor_t zc;
	zap_attribute_t attr;
	dsl_deadlist_t ll;
	/* NULL out os prior to dsl_deadlist_open in case it's garbage */
	ll.dl_os = NULL;
	for (zap_cursor_init(&zc, mos, zap_obj);
	    zap_cursor_retrieve(&zc, &attr) == 0;
	    (void) zap_cursor_advance(&zc)) {
		dsl_deadlist_open(&ll, mos, attr.za_first_integer);
		func(&ll, arg);
		dsl_deadlist_close(&ll);
	}
	zap_cursor_fini(&zc);
}