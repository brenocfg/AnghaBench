#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int zap_salt; } ;
typedef  TYPE_1__ zap_t ;
struct TYPE_7__ {int* zn_key_norm; int zn_key_intlen; int zn_key_norm_numints; scalar_t__ zn_key_orig; TYPE_1__* zn_zap; } ;
typedef  TYPE_2__ zap_name_t ;
typedef  int uint8_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int NBBY ; 
 int ZAP_FLAG_PRE_HASHED_KEY ; 
 int ZAP_FLAG_UINT64_KEY ; 
 scalar_t__ ZFS_CRC64_POLY ; 
 int zap_getflags (TYPE_1__*) ; 
 int zap_hashbits (TYPE_1__*) ; 
 scalar_t__* zfs_crc64_table ; 

__attribute__((used)) static uint64_t
zap_hash(zap_name_t *zn)
{
	zap_t *zap = zn->zn_zap;
	uint64_t h = 0;

	if (zap_getflags(zap) & ZAP_FLAG_PRE_HASHED_KEY) {
		ASSERT(zap_getflags(zap) & ZAP_FLAG_UINT64_KEY);
		h = *(uint64_t *)zn->zn_key_orig;
	} else {
		h = zap->zap_salt;
		ASSERT(h != 0);
		ASSERT(zfs_crc64_table[128] == ZFS_CRC64_POLY);

		if (zap_getflags(zap) & ZAP_FLAG_UINT64_KEY) {
			const uint64_t *wp = zn->zn_key_norm;

			ASSERT(zn->zn_key_intlen == 8);
			for (int i = 0; i < zn->zn_key_norm_numints;
			    wp++, i++) {
				uint64_t word = *wp;

				for (int j = 0; j < zn->zn_key_intlen; j++) {
					h = (h >> 8) ^
					    zfs_crc64_table[(h ^ word) & 0xFF];
					word >>= NBBY;
				}
			}
		} else {
			const uint8_t *cp = zn->zn_key_norm;

			/*
			 * We previously stored the terminating null on
			 * disk, but didn't hash it, so we need to
			 * continue to not hash it.  (The
			 * zn_key_*_numints includes the terminating
			 * null for non-binary keys.)
			 */
			int len = zn->zn_key_norm_numints - 1;

			ASSERT(zn->zn_key_intlen == 1);
			for (int i = 0; i < len; cp++, i++) {
				h = (h >> 8) ^
				    zfs_crc64_table[(h ^ *cp) & 0xFF];
			}
		}
	}
	/*
	 * Don't use all 64 bits, since we need some in the cookie for
	 * the collision differentiator.  We MUST use the high bits,
	 * since those are the ones that we first pay attention to when
	 * choosing the bucket.
	 */
	h &= ~((1ULL << (64 - zap_hashbits(zap))) - 1);

	return (h);
}