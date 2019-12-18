#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  hc_ocontext; int /*<<< orphan*/  hc_icontext; } ;
typedef  TYPE_1__ sha1_hmac_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA1_HMAC_BLOCK_SIZE ; 
 int SHA1_HMAC_INTS_PER_BLOCK ; 
 int /*<<< orphan*/  bcopy (void*,int*,int) ; 
 int /*<<< orphan*/  bzero (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sha1_mac_init_ctx(sha1_hmac_ctx_t *ctx, void *keyval, uint_t length_in_bytes)
{
	uint32_t ipad[SHA1_HMAC_INTS_PER_BLOCK];
	uint32_t opad[SHA1_HMAC_INTS_PER_BLOCK];
	uint_t i;

	bzero(ipad, SHA1_HMAC_BLOCK_SIZE);
	bzero(opad, SHA1_HMAC_BLOCK_SIZE);

	bcopy(keyval, ipad, length_in_bytes);
	bcopy(keyval, opad, length_in_bytes);

	/* XOR key with ipad (0x36) and opad (0x5c) */
	for (i = 0; i < SHA1_HMAC_INTS_PER_BLOCK; i++) {
		ipad[i] ^= 0x36363636;
		opad[i] ^= 0x5c5c5c5c;
	}

	/* perform SHA1 on ipad */
	SHA1Init(&ctx->hc_icontext);
	SHA1Update(&ctx->hc_icontext, (uint8_t *)ipad, SHA1_HMAC_BLOCK_SIZE);

	/* perform SHA1 on opad */
	SHA1Init(&ctx->hc_ocontext);
	SHA1Update(&ctx->hc_ocontext, (uint8_t *)opad, SHA1_HMAC_BLOCK_SIZE);
}