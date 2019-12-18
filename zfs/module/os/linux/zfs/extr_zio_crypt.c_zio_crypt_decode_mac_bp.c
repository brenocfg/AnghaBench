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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/ * zc_word; } ;
struct TYPE_9__ {TYPE_1__ blk_cksum; } ;
typedef  TYPE_2__ blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BP_GET_TYPE (TYPE_2__ const*) ; 
 scalar_t__ BP_IS_HOLE (TYPE_2__ const*) ; 
 int /*<<< orphan*/  BP_SHOULD_BYTESWAP (TYPE_2__ const*) ; 
 scalar_t__ BP_USES_CRYPT (TYPE_2__ const*) ; 
 int /*<<< orphan*/  BSWAP_64 (int /*<<< orphan*/ ) ; 
 scalar_t__ DMU_OT_OBJSET ; 
 int /*<<< orphan*/  ZIO_DATA_MAC_LEN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
zio_crypt_decode_mac_bp(const blkptr_t *bp, uint8_t *mac)
{
	uint64_t val64;

	ASSERT(BP_USES_CRYPT(bp) || BP_IS_HOLE(bp));

	/* for convenience, so callers don't need to check */
	if (BP_GET_TYPE(bp) == DMU_OT_OBJSET) {
		bzero(mac, ZIO_DATA_MAC_LEN);
		return;
	}

	if (!BP_SHOULD_BYTESWAP(bp)) {
		bcopy(&bp->blk_cksum.zc_word[2], mac, sizeof (uint64_t));
		bcopy(&bp->blk_cksum.zc_word[3], mac + sizeof (uint64_t),
		    sizeof (uint64_t));
	} else {
		val64 = BSWAP_64(bp->blk_cksum.zc_word[2]);
		bcopy(&val64, mac, sizeof (uint64_t));

		val64 = BSWAP_64(bp->blk_cksum.zc_word[3]);
		bcopy(&val64, mac + sizeof (uint64_t), sizeof (uint64_t));
	}
}