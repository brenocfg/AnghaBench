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
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  blkptr_auth_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  zio_crypt_bp_auth_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static void
zio_crypt_bp_do_aad_updates(uint8_t **aadp, uint_t *aad_len, uint64_t version,
    boolean_t should_bswap, blkptr_t *bp)
{
	uint_t bab_len;
	blkptr_auth_buf_t bab;

	zio_crypt_bp_auth_init(version, should_bswap, bp, &bab, &bab_len);
	bcopy(&bab, *aadp, bab_len);
	*aadp += bab_len;
	*aad_len += bab_len;
}