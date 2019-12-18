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
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  blkptr_auth_buf_t ;
typedef  int /*<<< orphan*/  SHA2_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA2Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_crypt_bp_auth_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zio_crypt_bp_do_indrect_checksum_updates(SHA2_CTX *ctx, uint64_t version,
    boolean_t should_bswap, blkptr_t *bp)
{
	uint_t bab_len;
	blkptr_auth_buf_t bab;

	zio_crypt_bp_auth_init(version, should_bswap, bp, &bab, &bab_len);
	SHA2Update(ctx, &bab, bab_len);
}