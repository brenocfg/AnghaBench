#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_18__ ;

/* Type definitions */
struct TYPE_30__ {int /*<<< orphan*/  tx_txg; } ;
typedef  TYPE_5__ dmu_tx_t ;
typedef  int /*<<< orphan*/  dmu_object_type_t ;
struct TYPE_31__ {int /*<<< orphan*/  db_size; } ;
typedef  TYPE_6__ dmu_buf_t ;
struct TYPE_32__ {int /*<<< orphan*/  db_level; TYPE_1__* db_objset; } ;
typedef  TYPE_7__ dmu_buf_impl_t ;
struct TYPE_29__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_28__ {TYPE_4__ member_0; } ;
struct TYPE_27__ {TYPE_3__ member_0; } ;
struct TYPE_33__ {TYPE_2__ member_0; } ;
typedef  TYPE_8__ blkptr_t ;
struct TYPE_26__ {int /*<<< orphan*/  os_dsl_dataset; } ;
struct TYPE_25__ {int /*<<< orphan*/  dn_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BPE_SET_LSIZE (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_BIRTH (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_LEVEL (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_REDACTED (TYPE_8__*) ; 
 int /*<<< orphan*/  BP_SET_TYPE (TYPE_8__*,int /*<<< orphan*/ ) ; 
 TYPE_18__* DB_DNODE (TYPE_7__*) ; 
 int /*<<< orphan*/  DB_DNODE_ENTER (TYPE_7__*) ; 
 int /*<<< orphan*/  DB_DNODE_EXIT (TYPE_7__*) ; 
 int /*<<< orphan*/  SPA_FEATURE_REDACTED_DATASETS ; 
 int /*<<< orphan*/  dbuf_override_impl (TYPE_7__*,TYPE_8__*,TYPE_5__*) ; 
 int /*<<< orphan*/  dmu_buf_will_not_fill (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  dsl_dataset_feature_is_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dmu_buf_redact(dmu_buf_t *dbuf, dmu_tx_t *tx)
{
	dmu_buf_impl_t *db = (dmu_buf_impl_t *)dbuf;
	dmu_object_type_t type;
	ASSERT(dsl_dataset_feature_is_active(db->db_objset->os_dsl_dataset,
	    SPA_FEATURE_REDACTED_DATASETS));

	DB_DNODE_ENTER(db);
	type = DB_DNODE(db)->dn_type;
	DB_DNODE_EXIT(db);

	ASSERT0(db->db_level);
	dmu_buf_will_not_fill(dbuf, tx);

	blkptr_t bp = { { { {0} } } };
	BP_SET_TYPE(&bp, type);
	BP_SET_LEVEL(&bp, 0);
	BP_SET_BIRTH(&bp, tx->tx_txg, 0);
	BP_SET_REDACTED(&bp);
	BPE_SET_LSIZE(&bp, dbuf->db_size);

	dbuf_override_impl(db, &bp, tx);
}