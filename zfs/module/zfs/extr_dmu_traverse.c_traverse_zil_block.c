#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zilog_t ;
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  td_arg; int /*<<< orphan*/  td_spa; int /*<<< orphan*/  (* td_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  td_objset; } ;
typedef  TYPE_2__ traverse_data_t ;
struct TYPE_7__ {int /*<<< orphan*/ * zc_word; } ;
struct TYPE_9__ {scalar_t__ blk_birth; TYPE_1__ blk_cksum; } ;
typedef  TYPE_3__ blkptr_t ;

/* Variables and functions */
 scalar_t__ BP_IS_HOLE (TYPE_3__*) ; 
 int /*<<< orphan*/  SET_BOOKMARK (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZB_ZIL_LEVEL ; 
 int /*<<< orphan*/  ZB_ZIL_OBJECT ; 
 size_t ZIL_ZC_SEQ ; 
 scalar_t__ spa_min_claim_txg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
traverse_zil_block(zilog_t *zilog, blkptr_t *bp, void *arg, uint64_t claim_txg)
{
	traverse_data_t *td = arg;
	zbookmark_phys_t zb;

	if (BP_IS_HOLE(bp))
		return (0);

	if (claim_txg == 0 && bp->blk_birth >= spa_min_claim_txg(td->td_spa))
		return (-1);

	SET_BOOKMARK(&zb, td->td_objset, ZB_ZIL_OBJECT, ZB_ZIL_LEVEL,
	    bp->blk_cksum.zc_word[ZIL_ZC_SEQ]);

	(void) td->td_func(td->td_spa, zilog, bp, &zb, NULL, td->td_arg);

	return (0);
}