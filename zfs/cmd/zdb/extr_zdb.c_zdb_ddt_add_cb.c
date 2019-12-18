#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zilog_t ;
struct TYPE_8__ {int zdde_ref_blocks; int /*<<< orphan*/  zdde_ref_dsize; int /*<<< orphan*/  zdde_ref_psize; int /*<<< orphan*/  zdde_ref_lsize; int /*<<< orphan*/  zdde_key; } ;
typedef  TYPE_1__ zdb_ddt_entry_t ;
struct TYPE_9__ {scalar_t__ zb_level; scalar_t__ zb_objset; } ;
typedef  TYPE_2__ zbookmark_phys_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  dnode_phys_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 scalar_t__ BP_GET_CHECKSUM (int /*<<< orphan*/  const*) ; 
 scalar_t__ BP_GET_FILL (int /*<<< orphan*/  const*) ; 
 scalar_t__ BP_GET_LEVEL (int /*<<< orphan*/  const*) ; 
 scalar_t__ BP_GET_LSIZE (int /*<<< orphan*/  const*) ; 
 scalar_t__ BP_GET_PSIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BP_GET_TYPE (int /*<<< orphan*/  const*) ; 
 scalar_t__ BP_IS_EMBEDDED (int /*<<< orphan*/  const*) ; 
 scalar_t__ BP_IS_HOLE (int /*<<< orphan*/  const*) ; 
 scalar_t__ DMU_OT_IS_METADATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 scalar_t__ ZB_DNODE_LEVEL ; 
 scalar_t__ ZB_ROOT_LEVEL ; 
 scalar_t__ ZIO_CHECKSUM_OFF ; 
 TYPE_1__* avl_find (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_insert (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avl_numnodes (int /*<<< orphan*/ *) ; 
 scalar_t__ bp_get_dsize_sync (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ddt_key_fill (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int* dump_opt ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* umem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zdb_ddt_add_cb(spa_t *spa, zilog_t *zilog, const blkptr_t *bp,
    const zbookmark_phys_t *zb, const dnode_phys_t *dnp, void *arg)
{
	avl_tree_t *t = arg;
	avl_index_t where;
	zdb_ddt_entry_t *zdde, zdde_search;

	if (zb->zb_level == ZB_DNODE_LEVEL || BP_IS_HOLE(bp) ||
	    BP_IS_EMBEDDED(bp))
		return (0);

	if (dump_opt['S'] > 1 && zb->zb_level == ZB_ROOT_LEVEL) {
		(void) printf("traversing objset %llu, %llu objects, "
		    "%lu blocks so far\n",
		    (u_longlong_t)zb->zb_objset,
		    (u_longlong_t)BP_GET_FILL(bp),
		    avl_numnodes(t));
	}

	if (BP_IS_HOLE(bp) || BP_GET_CHECKSUM(bp) == ZIO_CHECKSUM_OFF ||
	    BP_GET_LEVEL(bp) > 0 || DMU_OT_IS_METADATA(BP_GET_TYPE(bp)))
		return (0);

	ddt_key_fill(&zdde_search.zdde_key, bp);

	zdde = avl_find(t, &zdde_search, &where);

	if (zdde == NULL) {
		zdde = umem_zalloc(sizeof (*zdde), UMEM_NOFAIL);
		zdde->zdde_key = zdde_search.zdde_key;
		avl_insert(t, zdde, where);
	}

	zdde->zdde_ref_blocks += 1;
	zdde->zdde_ref_lsize += BP_GET_LSIZE(bp);
	zdde->zdde_ref_psize += BP_GET_PSIZE(bp);
	zdde->zdde_ref_dsize += bp_get_dsize_sync(spa, bp);

	return (0);
}