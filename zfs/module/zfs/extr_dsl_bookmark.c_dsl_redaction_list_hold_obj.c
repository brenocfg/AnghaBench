#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_15__ {int /*<<< orphan*/  rl_dbu; TYPE_3__* rl_dbuf; int /*<<< orphan*/  rl_longholds; int /*<<< orphan*/ * rl_mos; int /*<<< orphan*/  rl_phys; int /*<<< orphan*/  rl_object; } ;
typedef  TYPE_1__ redaction_list_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_16__ {int /*<<< orphan*/ * dp_meta_objset; } ;
typedef  TYPE_2__ dsl_pool_t ;
struct TYPE_17__ {int /*<<< orphan*/  db_data; } ;
typedef  TYPE_3__ dmu_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int dmu_bonus_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,TYPE_3__**) ; 
 TYPE_1__* dmu_buf_get_user (TYPE_3__*) ; 
 int /*<<< orphan*/  dmu_buf_init_user (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__**) ; 
 TYPE_1__* dmu_buf_set_user_ie (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_config_held (TYPE_2__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redaction_list_evict_sync ; 
 int /*<<< orphan*/  zfs_refcount_create (int /*<<< orphan*/ *) ; 

int
dsl_redaction_list_hold_obj(dsl_pool_t *dp, uint64_t rlobj, void *tag,
    redaction_list_t **rlp)
{
	objset_t *mos = dp->dp_meta_objset;
	dmu_buf_t *dbuf;
	redaction_list_t *rl;
	int err;

	ASSERT(dsl_pool_config_held(dp));

	err = dmu_bonus_hold(mos, rlobj, tag, &dbuf);
	if (err != 0)
		return (err);

	rl = dmu_buf_get_user(dbuf);
	if (rl == NULL) {
		redaction_list_t *winner = NULL;

		rl = kmem_zalloc(sizeof (redaction_list_t), KM_SLEEP);
		rl->rl_dbuf = dbuf;
		rl->rl_object = rlobj;
		rl->rl_phys = dbuf->db_data;
		rl->rl_mos = dp->dp_meta_objset;
		zfs_refcount_create(&rl->rl_longholds);
		dmu_buf_init_user(&rl->rl_dbu, redaction_list_evict_sync, NULL,
		    &rl->rl_dbuf);
		if ((winner = dmu_buf_set_user_ie(dbuf, &rl->rl_dbu)) != NULL) {
			kmem_free(rl, sizeof (*rl));
			rl = winner;
		}
	}
	*rlp = rl;
	return (0);
}