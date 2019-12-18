#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
struct drr_spill {void* drr_compressed_size; int /*<<< orphan*/  drr_mac; int /*<<< orphan*/  drr_iv; int /*<<< orphan*/  drr_salt; int /*<<< orphan*/  drr_compressiontype; int /*<<< orphan*/  drr_flags; int /*<<< orphan*/  drr_toguid; void* drr_length; void* drr_object; } ;
struct TYPE_16__ {scalar_t__ dsc_pending_op; scalar_t__ dsc_fromtxg; int dsc_featureflags; int /*<<< orphan*/  dsc_toguid; TYPE_9__* dsc_drr; } ;
typedef  TYPE_2__ dmu_send_cookie_t ;
typedef  int /*<<< orphan*/  dmu_replay_record_t ;
struct TYPE_17__ {scalar_t__ blk_birth; } ;
typedef  TYPE_3__ blkptr_t ;
struct TYPE_15__ {struct drr_spill drr_spill; } ;
struct TYPE_18__ {int /*<<< orphan*/  drr_type; TYPE_1__ drr_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_GET_COMPRESS (TYPE_3__ const*) ; 
 void* BP_GET_LSIZE (TYPE_3__ const*) ; 
 void* BP_GET_PSIZE (TYPE_3__ const*) ; 
 int /*<<< orphan*/  BP_IS_PROTECTED (TYPE_3__ const*) ; 
 scalar_t__ BP_SHOULD_BYTESWAP (TYPE_3__ const*) ; 
 int DMU_BACKUP_FEATURE_RAW ; 
 int /*<<< orphan*/  DRR_RAW_BYTESWAP ; 
 int /*<<< orphan*/  DRR_SPILL ; 
 int /*<<< orphan*/  DRR_SPILL_UNMODIFIED ; 
 int /*<<< orphan*/  EINTR ; 
 scalar_t__ PENDING_NONE ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_9__*,int) ; 
 scalar_t__ dump_record (TYPE_2__*,void*,void*) ; 
 scalar_t__ zfs_send_unmodified_spill_blocks ; 
 int /*<<< orphan*/  zio_crypt_decode_mac_bp (TYPE_3__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_crypt_decode_params_bp (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dump_spill(dmu_send_cookie_t *dscp, const blkptr_t *bp, uint64_t object,
    void *data)
{
	struct drr_spill *drrs = &(dscp->dsc_drr->drr_u.drr_spill);
	uint64_t blksz = BP_GET_LSIZE(bp);
	uint64_t payload_size = blksz;

	if (dscp->dsc_pending_op != PENDING_NONE) {
		if (dump_record(dscp, NULL, 0) != 0)
			return (SET_ERROR(EINTR));
		dscp->dsc_pending_op = PENDING_NONE;
	}

	/* write a SPILL record */
	bzero(dscp->dsc_drr, sizeof (dmu_replay_record_t));
	dscp->dsc_drr->drr_type = DRR_SPILL;
	drrs->drr_object = object;
	drrs->drr_length = blksz;
	drrs->drr_toguid = dscp->dsc_toguid;

	/* See comment in dump_dnode() for full details */
	if (zfs_send_unmodified_spill_blocks &&
	    (bp->blk_birth <= dscp->dsc_fromtxg)) {
		drrs->drr_flags |= DRR_SPILL_UNMODIFIED;
	}

	/* handle raw send fields */
	if (dscp->dsc_featureflags & DMU_BACKUP_FEATURE_RAW) {
		ASSERT(BP_IS_PROTECTED(bp));

		if (BP_SHOULD_BYTESWAP(bp))
			drrs->drr_flags |= DRR_RAW_BYTESWAP;
		drrs->drr_compressiontype = BP_GET_COMPRESS(bp);
		drrs->drr_compressed_size = BP_GET_PSIZE(bp);
		zio_crypt_decode_params_bp(bp, drrs->drr_salt, drrs->drr_iv);
		zio_crypt_decode_mac_bp(bp, drrs->drr_mac);
		payload_size = drrs->drr_compressed_size;
	}

	if (dump_record(dscp, data, payload_size) != 0)
		return (SET_ERROR(EINTR));
	return (0);
}