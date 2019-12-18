#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_11__ {int /*<<< orphan*/  blk_prop; } ;
typedef  TYPE_1__ blkptr_t ;
struct TYPE_12__ {unsigned long long bab_pad; int /*<<< orphan*/  bab_prop; int /*<<< orphan*/  bab_mac; } ;
typedef  TYPE_2__ blkptr_auth_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_IS_EMBEDDED (TYPE_1__*) ; 
 scalar_t__ BP_IS_HOLE (TYPE_1__*) ; 
 scalar_t__ BP_USES_CRYPT (TYPE_1__*) ; 
 int /*<<< orphan*/  LE_64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  byteswap_uint64_array (TYPE_1__*,int) ; 
 int /*<<< orphan*/  zio_crypt_bp_zero_nonportable_blkprop (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_crypt_decode_mac_bp (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zio_crypt_bp_auth_init(uint64_t version, boolean_t should_bswap, blkptr_t *bp,
    blkptr_auth_buf_t *bab, uint_t *bab_len)
{
	blkptr_t tmpbp = *bp;

	if (should_bswap)
		byteswap_uint64_array(&tmpbp, sizeof (blkptr_t));

	ASSERT(BP_USES_CRYPT(&tmpbp) || BP_IS_HOLE(&tmpbp));
	ASSERT0(BP_IS_EMBEDDED(&tmpbp));

	zio_crypt_decode_mac_bp(&tmpbp, bab->bab_mac);

	/*
	 * We always MAC blk_prop in LE to ensure portability. This
	 * must be done after decoding the mac, since the endianness
	 * will get zero'd out here.
	 */
	zio_crypt_bp_zero_nonportable_blkprop(&tmpbp, version);
	bab->bab_prop = LE_64(tmpbp.blk_prop);
	bab->bab_pad = 0ULL;

	/* version 0 did not include the padding */
	*bab_len = sizeof (blkptr_auth_buf_t);
	if (version == 0)
		*bab_len -= sizeof (uint64_t);
}