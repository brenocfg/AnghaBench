#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct receive_writer_arg {int byteswap; scalar_t__ max_object; scalar_t__ or_firstobj; scalar_t__ or_numslots; int or_byteorder; int /*<<< orphan*/  or_mac; int /*<<< orphan*/  or_iv; int /*<<< orphan*/  or_salt; int /*<<< orphan*/  or_crypt_params_present; int /*<<< orphan*/  raw; } ;
struct drr_object_range {scalar_t__ drr_numslots; scalar_t__ drr_firstobj; int /*<<< orphan*/  drr_mac; int /*<<< orphan*/  drr_iv; int /*<<< orphan*/  drr_salt; int /*<<< orphan*/  drr_flags; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ DNODES_PER_BLOCK ; 
 int /*<<< orphan*/  DRR_IS_RAW_BYTESWAPPED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ P2PHASE (scalar_t__,scalar_t__) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZFS_HOST_BYTEORDER ; 
 int /*<<< orphan*/  ZIO_DATA_IV_LEN ; 
 int /*<<< orphan*/  ZIO_DATA_MAC_LEN ; 
 int /*<<< orphan*/  ZIO_DATA_SALT_LEN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
receive_object_range(struct receive_writer_arg *rwa,
    struct drr_object_range *drror)
{
	/*
	 * By default, we assume this block is in our native format
	 * (ZFS_HOST_BYTEORDER). We then take into account whether
	 * the send stream is byteswapped (rwa->byteswap). Finally,
	 * we need to byteswap again if this particular block was
	 * in non-native format on the send side.
	 */
	boolean_t byteorder = ZFS_HOST_BYTEORDER ^ rwa->byteswap ^
	    !!DRR_IS_RAW_BYTESWAPPED(drror->drr_flags);

	/*
	 * Since dnode block sizes are constant, we should not need to worry
	 * about making sure that the dnode block size is the same on the
	 * sending and receiving sides for the time being. For non-raw sends,
	 * this does not matter (and in fact we do not send a DRR_OBJECT_RANGE
	 * record at all). Raw sends require this record type because the
	 * encryption parameters are used to protect an entire block of bonus
	 * buffers. If the size of dnode blocks ever becomes variable,
	 * handling will need to be added to ensure that dnode block sizes
	 * match on the sending and receiving side.
	 */
	if (drror->drr_numslots != DNODES_PER_BLOCK ||
	    P2PHASE(drror->drr_firstobj, DNODES_PER_BLOCK) != 0 ||
	    !rwa->raw)
		return (SET_ERROR(EINVAL));

	if (drror->drr_firstobj > rwa->max_object)
		rwa->max_object = drror->drr_firstobj;

	/*
	 * The DRR_OBJECT_RANGE handling must be deferred to receive_object()
	 * so that the block of dnodes is not written out when it's empty,
	 * and converted to a HOLE BP.
	 */
	rwa->or_crypt_params_present = B_TRUE;
	rwa->or_firstobj = drror->drr_firstobj;
	rwa->or_numslots = drror->drr_numslots;
	bcopy(drror->drr_salt, rwa->or_salt, ZIO_DATA_SALT_LEN);
	bcopy(drror->drr_iv, rwa->or_iv, ZIO_DATA_IV_LEN);
	bcopy(drror->drr_mac, rwa->or_mac, ZIO_DATA_MAC_LEN);
	rwa->or_byteorder = byteorder;

	return (0);
}