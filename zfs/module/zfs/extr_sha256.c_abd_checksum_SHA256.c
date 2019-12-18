#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void** zc_word; } ;
typedef  TYPE_1__ zio_cksum_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  abd_t ;
typedef  int /*<<< orphan*/  SHA2_CTX ;

/* Variables and functions */
 void* BE_64 (void*) ; 
 int CPA_STATUS_SUCCESS ; 
 int /*<<< orphan*/  SHA256 ; 
 int /*<<< orphan*/  SHA2Final (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA2Init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZIO_CHECKSUM_SHA256 ; 
 int /*<<< orphan*/ * abd_borrow_buf_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_iterate_func (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abd_return_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int qat_checksum (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ qat_checksum_use_accel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sha_incremental ; 

void
abd_checksum_SHA256(abd_t *abd, uint64_t size,
    const void *ctx_template, zio_cksum_t *zcp)
{
	int ret;
	SHA2_CTX ctx;
	zio_cksum_t tmp;

	if (qat_checksum_use_accel(size)) {
		uint8_t *buf = abd_borrow_buf_copy(abd, size);
		ret = qat_checksum(ZIO_CHECKSUM_SHA256, buf, size, &tmp);
		abd_return_buf(abd, buf, size);
		if (ret == CPA_STATUS_SUCCESS)
			goto bswap;

		/* If the hardware implementation fails fall back to software */
	}

	SHA2Init(SHA256, &ctx);
	(void) abd_iterate_func(abd, 0, size, sha_incremental, &ctx);
	SHA2Final(&tmp, &ctx);

bswap:
	/*
	 * A prior implementation of this function had a
	 * private SHA256 implementation always wrote things out in
	 * Big Endian and there wasn't a byteswap variant of it.
	 * To preserve on disk compatibility we need to force that
	 * behavior.
	 */
	zcp->zc_word[0] = BE_64(tmp.zc_word[0]);
	zcp->zc_word[1] = BE_64(tmp.zc_word[1]);
	zcp->zc_word[2] = BE_64(tmp.zc_word[2]);
	zcp->zc_word[3] = BE_64(tmp.zc_word[3]);
}