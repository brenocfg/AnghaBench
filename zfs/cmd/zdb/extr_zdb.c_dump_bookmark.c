#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ zbm_redaction_obj; scalar_t__ zbm_creation_time; scalar_t__ zbm_creation_txg; scalar_t__ zbm_guid; } ;
typedef  TYPE_2__ zfs_bookmark_phys_t ;
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int u_longlong_t ;
struct TYPE_22__ {TYPE_4__* rl_phys; } ;
typedef  TYPE_3__ redaction_list_t ;
struct TYPE_23__ {scalar_t__ rlp_last_object; scalar_t__ rlp_last_blkid; unsigned int rlp_num_snaps; scalar_t__ rlp_num_entries; scalar_t__* rlp_snaps; } ;
typedef  TYPE_4__ redaction_list_phys_t ;
struct TYPE_24__ {scalar_t__ rbp_object; scalar_t__ rbp_blkid; } ;
typedef  TYPE_5__ redact_block_phys_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_25__ {TYPE_1__* dp_spa; } ;
typedef  TYPE_6__ dsl_pool_t ;
struct TYPE_26__ {int /*<<< orphan*/  doi_max_offset; } ;
typedef  TYPE_7__ dmu_object_info_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_20__ {int /*<<< orphan*/ * spa_meta_objset; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  IMPLY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_object_info (int /*<<< orphan*/ *,scalar_t__,TYPE_7__*) ; 
 int dmu_read (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int dsl_bookmark_lookup (TYPE_6__*,char*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_redaction_list_hold_obj (TYPE_6__*,scalar_t__,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  dsl_redaction_list_rele (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* kmem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ redact_block_get_count (TYPE_5__*) ; 
 scalar_t__ redact_block_get_size (TYPE_5__*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int
dump_bookmark(dsl_pool_t *dp, char *name, boolean_t print_redact,
    boolean_t print_list)
{
	int err = 0;
	zfs_bookmark_phys_t prop;
	objset_t *mos = dp->dp_spa->spa_meta_objset;
	err = dsl_bookmark_lookup(dp, name, NULL, &prop);

	if (err != 0) {
		return (err);
	}

	(void) printf("\t#%s: ", strchr(name, '#') + 1);
	(void) printf("{guid: %llx creation_txg: %llu creation_time: "
	    "%llu redaction_obj: %llu}\n", (u_longlong_t)prop.zbm_guid,
	    (u_longlong_t)prop.zbm_creation_txg,
	    (u_longlong_t)prop.zbm_creation_time,
	    (u_longlong_t)prop.zbm_redaction_obj);

	IMPLY(print_list, print_redact);
	if (!print_redact || prop.zbm_redaction_obj == 0)
		return (0);

	redaction_list_t *rl;
	VERIFY0(dsl_redaction_list_hold_obj(dp,
	    prop.zbm_redaction_obj, FTAG, &rl));

	redaction_list_phys_t *rlp = rl->rl_phys;
	(void) printf("\tRedacted:\n\t\tProgress: ");
	if (rlp->rlp_last_object != UINT64_MAX ||
	    rlp->rlp_last_blkid != UINT64_MAX) {
		(void) printf("%llu %llu (incomplete)\n",
		    (u_longlong_t)rlp->rlp_last_object,
		    (u_longlong_t)rlp->rlp_last_blkid);
	} else {
		(void) printf("complete\n");
	}
	(void) printf("\t\tSnapshots: [");
	for (unsigned int i = 0; i < rlp->rlp_num_snaps; i++) {
		if (i > 0)
			(void) printf(", ");
		(void) printf("%0llu",
		    (u_longlong_t)rlp->rlp_snaps[i]);
	}
	(void) printf("]\n\t\tLength: %llu\n",
	    (u_longlong_t)rlp->rlp_num_entries);

	if (!print_list) {
		dsl_redaction_list_rele(rl, FTAG);
		return (0);
	}

	if (rlp->rlp_num_entries == 0) {
		dsl_redaction_list_rele(rl, FTAG);
		(void) printf("\t\tRedaction List: []\n\n");
		return (0);
	}

	redact_block_phys_t *rbp_buf;
	uint64_t size;
	dmu_object_info_t doi;

	VERIFY0(dmu_object_info(mos, prop.zbm_redaction_obj, &doi));
	size = doi.doi_max_offset;
	rbp_buf = kmem_alloc(size, KM_SLEEP);

	err = dmu_read(mos, prop.zbm_redaction_obj, 0, size,
	    rbp_buf, 0);
	if (err != 0) {
		dsl_redaction_list_rele(rl, FTAG);
		kmem_free(rbp_buf, size);
		return (err);
	}

	(void) printf("\t\tRedaction List: [{object: %llx, offset: "
	    "%llx, blksz: %x, count: %llx}",
	    (u_longlong_t)rbp_buf[0].rbp_object,
	    (u_longlong_t)rbp_buf[0].rbp_blkid,
	    (uint_t)(redact_block_get_size(&rbp_buf[0])),
	    (u_longlong_t)redact_block_get_count(&rbp_buf[0]));

	for (size_t i = 1; i < rlp->rlp_num_entries; i++) {
		(void) printf(",\n\t\t{object: %llx, offset: %llx, "
		    "blksz: %x, count: %llx}",
		    (u_longlong_t)rbp_buf[i].rbp_object,
		    (u_longlong_t)rbp_buf[i].rbp_blkid,
		    (uint_t)(redact_block_get_size(&rbp_buf[i])),
		    (u_longlong_t)redact_block_get_count(&rbp_buf[i]));
	}
	dsl_redaction_list_rele(rl, FTAG);
	kmem_free(rbp_buf, size);
	(void) printf("]\n\n");
	return (0);
}