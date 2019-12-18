#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong_t ;
typedef  int u_longlong_t ;
typedef  int longlong_t ;
struct TYPE_16__ {TYPE_1__* dn_objset; int /*<<< orphan*/  dn_holds; } ;
typedef  TYPE_3__ dnode_t ;
struct TYPE_17__ {scalar_t__ doi_max_offset; scalar_t__ doi_fill_count; scalar_t__ doi_indirection; scalar_t__ doi_bonus_size; scalar_t__ doi_metadata_block_size; scalar_t__ doi_data_block_size; int /*<<< orphan*/  doi_bonus_type; int /*<<< orphan*/  doi_type; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ dmu_object_info_t ;
struct TYPE_15__ {scalar_t__ db_object; scalar_t__ db_size; scalar_t__ db_offset; } ;
struct TYPE_18__ {TYPE_2__ db; int /*<<< orphan*/  db_objset; int /*<<< orphan*/  db_cache_link; int /*<<< orphan*/  db_holds; int /*<<< orphan*/  db_state; scalar_t__ db_blkid; scalar_t__ db_level; scalar_t__ db_buf; } ;
typedef  TYPE_5__ dmu_buf_impl_t ;
struct TYPE_19__ {scalar_t__ abi_holds; int /*<<< orphan*/  abi_l2arc_compress; scalar_t__ abi_l2arc_asize; scalar_t__ abi_l2arc_dattr; scalar_t__ abi_l2arc_hits; scalar_t__ abi_mfu_ghost_hits; scalar_t__ abi_mfu_hits; scalar_t__ abi_mru_ghost_hits; scalar_t__ abi_mru_hits; scalar_t__ abi_access; scalar_t__ abi_size; scalar_t__ abi_bufcnt; int /*<<< orphan*/  abi_flags; int /*<<< orphan*/  abi_state_contents; int /*<<< orphan*/  abi_state_type; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_6__ arc_buf_info_t ;
struct TYPE_14__ {int /*<<< orphan*/  os_spa; } ;

/* Variables and functions */
 TYPE_3__* DB_DNODE (TYPE_5__*) ; 
 int /*<<< orphan*/  __dmu_object_info_from_dnode (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  arc_buf_info (scalar_t__,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbuf_is_metadata (TYPE_5__*) ; 
 scalar_t__ dmu_objset_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multilist_link_active (int /*<<< orphan*/ *) ; 
 size_t snprintf (char*,size_t,char*,char*,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 char* spa_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_dbuf_state_index ; 
 scalar_t__ zfs_refcount_count (int /*<<< orphan*/ *) ; 

int
__dbuf_stats_hash_table_data(char *buf, size_t size, dmu_buf_impl_t *db)
{
	arc_buf_info_t abi = { 0 };
	dmu_object_info_t doi = { 0 };
	dnode_t *dn = DB_DNODE(db);
	size_t nwritten;

	if (db->db_buf)
		arc_buf_info(db->db_buf, &abi, zfs_dbuf_state_index);

	__dmu_object_info_from_dnode(dn, &doi);

	nwritten = snprintf(buf, size,
	    "%-16s %-8llu %-8lld %-8lld %-8lld %-10llu %-8llu %-5d %-5d "
	    "%-7lu %-3d | %-5d %-5d 0x%-7x %-6lu %-8llu %-12llu "
	    "%-6lu %-6lu %-6lu %-6lu %-6lu %-8llu %-8llu %-8d %-6lu | "
	    "%-6d %-6d %-8lu %-8lu %-6llu %-6lu %-6lu %-8llu %-8llu\n",
	    /* dmu_buf_impl_t */
	    spa_name(dn->dn_objset->os_spa),
	    (u_longlong_t)dmu_objset_id(db->db_objset),
	    (longlong_t)db->db.db_object,
	    (longlong_t)db->db_level,
	    (longlong_t)db->db_blkid,
	    (u_longlong_t)db->db.db_offset,
	    (u_longlong_t)db->db.db_size,
	    !!dbuf_is_metadata(db),
	    db->db_state,
	    (ulong_t)zfs_refcount_count(&db->db_holds),
	    multilist_link_active(&db->db_cache_link),
	    /* arc_buf_info_t */
	    abi.abi_state_type,
	    abi.abi_state_contents,
	    abi.abi_flags,
	    (ulong_t)abi.abi_bufcnt,
	    (u_longlong_t)abi.abi_size,
	    (u_longlong_t)abi.abi_access,
	    (ulong_t)abi.abi_mru_hits,
	    (ulong_t)abi.abi_mru_ghost_hits,
	    (ulong_t)abi.abi_mfu_hits,
	    (ulong_t)abi.abi_mfu_ghost_hits,
	    (ulong_t)abi.abi_l2arc_hits,
	    (u_longlong_t)abi.abi_l2arc_dattr,
	    (u_longlong_t)abi.abi_l2arc_asize,
	    abi.abi_l2arc_compress,
	    (ulong_t)abi.abi_holds,
	    /* dmu_object_info_t */
	    doi.doi_type,
	    doi.doi_bonus_type,
	    (ulong_t)doi.doi_data_block_size,
	    (ulong_t)doi.doi_metadata_block_size,
	    (u_longlong_t)doi.doi_bonus_size,
	    (ulong_t)doi.doi_indirection,
	    (ulong_t)zfs_refcount_count(&dn->dn_holds),
	    (u_longlong_t)doi.doi_fill_count,
	    (u_longlong_t)doi.doi_max_offset);

	if (nwritten >= size)
		return (size);

	return (nwritten + 1);
}