#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zilog_t ;
struct TYPE_12__ {scalar_t__ zb_level; scalar_t__ zb_object; int zb_blkid; } ;
typedef  TYPE_1__ zbookmark_phys_t ;
typedef  int uint64_t ;
struct diffarg {int dummy; } ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_13__ {scalar_t__ dn_extra_slots; } ;
typedef  TYPE_2__ dnode_phys_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  arc_flags_t ;
struct TYPE_14__ {TYPE_2__* b_data; } ;
typedef  TYPE_3__ arc_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_FLAG_WAIT ; 
 int BP_GET_LSIZE (int /*<<< orphan*/  const*) ; 
 scalar_t__ BP_IS_HOLE (int /*<<< orphan*/  const*) ; 
 scalar_t__ BP_IS_PROTECTED (int /*<<< orphan*/  const*) ; 
 int DBP_SPAN (TYPE_2__ const*,scalar_t__) ; 
 scalar_t__ DMU_META_DNODE_OBJECT ; 
 int DNODE_BLOCK_SHIFT ; 
 int DNODE_SHIFT ; 
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  FORREAL ; 
 int /*<<< orphan*/  JUSTLOOKING ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int TRAVERSE_VISIT_NO_CHILDREN ; 
 scalar_t__ ZB_DNODE_LEVEL ; 
 int ZIO_FLAG_CANFAIL ; 
 int ZIO_FLAG_RAW ; 
 int /*<<< orphan*/  ZIO_PRIORITY_ASYNC_READ ; 
 int /*<<< orphan*/  arc_buf_destroy (TYPE_3__*,TYPE_3__**) ; 
 int /*<<< orphan*/  arc_getbuf_func ; 
 scalar_t__ arc_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_3__**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 scalar_t__ issig (int /*<<< orphan*/ ) ; 
 int report_dnode (struct diffarg*,int,TYPE_2__*) ; 
 int report_free_dnode_range (struct diffarg*,int,int) ; 

__attribute__((used)) static int
diff_cb(spa_t *spa, zilog_t *zilog, const blkptr_t *bp,
    const zbookmark_phys_t *zb, const dnode_phys_t *dnp, void *arg)
{
	struct diffarg *da = arg;
	int err = 0;

	if (issig(JUSTLOOKING) && issig(FORREAL))
		return (SET_ERROR(EINTR));

	if (zb->zb_level == ZB_DNODE_LEVEL ||
	    zb->zb_object != DMU_META_DNODE_OBJECT)
		return (0);

	if (BP_IS_HOLE(bp)) {
		uint64_t span = DBP_SPAN(dnp, zb->zb_level);
		uint64_t dnobj = (zb->zb_blkid * span) >> DNODE_SHIFT;

		err = report_free_dnode_range(da, dnobj,
		    dnobj + (span >> DNODE_SHIFT) - 1);
		if (err)
			return (err);
	} else if (zb->zb_level == 0) {
		dnode_phys_t *blk;
		arc_buf_t *abuf;
		arc_flags_t aflags = ARC_FLAG_WAIT;
		int epb = BP_GET_LSIZE(bp) >> DNODE_SHIFT;
		int zio_flags = ZIO_FLAG_CANFAIL;
		int i;

		if (BP_IS_PROTECTED(bp))
			zio_flags |= ZIO_FLAG_RAW;

		if (arc_read(NULL, spa, bp, arc_getbuf_func, &abuf,
		    ZIO_PRIORITY_ASYNC_READ, zio_flags, &aflags, zb) != 0)
			return (SET_ERROR(EIO));

		blk = abuf->b_data;
		for (i = 0; i < epb; i += blk[i].dn_extra_slots + 1) {
			uint64_t dnobj = (zb->zb_blkid <<
			    (DNODE_BLOCK_SHIFT - DNODE_SHIFT)) + i;
			err = report_dnode(da, dnobj, blk+i);
			if (err)
				break;
		}
		arc_buf_destroy(abuf, &abuf);
		if (err)
			return (err);
		/* Don't care about the data blocks */
		return (TRAVERSE_VISIT_NO_CHILDREN);
	}
	return (0);
}