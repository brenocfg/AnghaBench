#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ztest_ds_t ;
struct TYPE_4__ {scalar_t__ zl_parse_lr_count; scalar_t__ zl_replaying_seq; scalar_t__ zl_parse_blk_count; } ;
typedef  TYPE_1__ zilog_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_5__ {int zo_verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DMU_OST_ANY ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_disown (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* dmu_objset_zil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * umem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umem_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zil_replay (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ztest_dmu_objset_own (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 TYPE_2__ ztest_opts ; 
 int /*<<< orphan*/  ztest_replay_vector ; 
 int /*<<< orphan*/  ztest_zd_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ztest_zd_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ztest_replay_zil_cb(const char *name, void *arg)
{
	objset_t *os;
	ztest_ds_t *zdtmp;

	VERIFY0(ztest_dmu_objset_own(name, DMU_OST_ANY, B_TRUE,
	    B_TRUE, FTAG, &os));

	zdtmp = umem_alloc(sizeof (ztest_ds_t), UMEM_NOFAIL);

	ztest_zd_init(zdtmp, NULL, os);
	zil_replay(os, zdtmp, ztest_replay_vector);
	ztest_zd_fini(zdtmp);

	if (dmu_objset_zil(os)->zl_parse_lr_count != 0 &&
	    ztest_opts.zo_verbose >= 6) {
		zilog_t *zilog = dmu_objset_zil(os);

		(void) printf("%s replay %llu blocks, %llu records, seq %llu\n",
		    name,
		    (u_longlong_t)zilog->zl_parse_blk_count,
		    (u_longlong_t)zilog->zl_parse_lr_count,
		    (u_longlong_t)zilog->zl_replaying_seq);
	}

	umem_free(zdtmp, sizeof (ztest_ds_t));

	dmu_objset_disown(os, B_TRUE, FTAG);
	return (0);
}