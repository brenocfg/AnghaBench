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
typedef  int uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  SHA2_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ECKSUM ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA2Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA2Init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA512 ; 
 int SHA512_DIGEST_LENGTH ; 
 int SPA_BLKPTRSHIFT ; 
 int /*<<< orphan*/  ZIO_DATA_MAC_LEN ; 
 scalar_t__ bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_crypt_bp_do_indrect_checksum_updates (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zio_crypt_do_indirect_mac_checksum_impl(boolean_t generate, void *buf,
    uint_t datalen, uint64_t version, boolean_t byteswap, uint8_t *cksum)
{
	blkptr_t *bp;
	int i, epb = datalen >> SPA_BLKPTRSHIFT;
	SHA2_CTX ctx;
	uint8_t digestbuf[SHA512_DIGEST_LENGTH];

	/* checksum all of the MACs from the layer below */
	SHA2Init(SHA512, &ctx);
	for (i = 0, bp = buf; i < epb; i++, bp++) {
		zio_crypt_bp_do_indrect_checksum_updates(&ctx, version,
		    byteswap, bp);
	}
	SHA2Final(digestbuf, &ctx);

	if (generate) {
		bcopy(digestbuf, cksum, ZIO_DATA_MAC_LEN);
		return (0);
	}

	if (bcmp(digestbuf, cksum, ZIO_DATA_MAC_LEN) != 0)
		return (SET_ERROR(ECKSUM));

	return (0);
}