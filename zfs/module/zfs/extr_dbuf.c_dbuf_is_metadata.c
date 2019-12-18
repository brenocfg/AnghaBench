#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ db_level; scalar_t__ db_blkid; } ;
typedef  TYPE_1__ dmu_buf_impl_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/  dn_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 TYPE_5__* DB_DNODE (TYPE_1__*) ; 
 int /*<<< orphan*/  DB_DNODE_ENTER (TYPE_1__*) ; 
 int /*<<< orphan*/  DB_DNODE_EXIT (TYPE_1__*) ; 
 int /*<<< orphan*/  DMU_OT_IS_METADATA (int /*<<< orphan*/ ) ; 
 scalar_t__ DMU_SPILL_BLKID ; 

boolean_t
dbuf_is_metadata(dmu_buf_impl_t *db)
{
	/*
	 * Consider indirect blocks and spill blocks to be meta data.
	 */
	if (db->db_level > 0 || db->db_blkid == DMU_SPILL_BLKID) {
		return (B_TRUE);
	} else {
		boolean_t is_metadata;

		DB_DNODE_ENTER(db);
		is_metadata = DMU_OT_IS_METADATA(DB_DNODE(db)->dn_type);
		DB_DNODE_EXIT(db);

		return (is_metadata);
	}
}