#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/ * ks32; } ;
struct TYPE_5__ {int /*<<< orphan*/  nr; TYPE_1__ decr_ks; TYPE_3__* ops; } ;
typedef  TYPE_2__ aes_key_t ;
struct TYPE_6__ {scalar_t__ needs_byteswap; int /*<<< orphan*/  (* decrypt ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ aes_impl_ops_t ;

/* Variables and functions */
 int AES_BLOCK_LEN ; 
 int CRYPTO_SUCCESS ; 
 scalar_t__ IS_P2ALIGNED2 (int /*<<< orphan*/ * const*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
aes_decrypt_block(const void *ks, const uint8_t *ct, uint8_t *pt)
{
	aes_key_t	*ksch = (aes_key_t *)ks;
	const aes_impl_ops_t	*ops = ksch->ops;

	if (IS_P2ALIGNED2(ct, pt, sizeof (uint32_t)) && !ops->needs_byteswap) {
		/* LINTED:  pointer alignment */
		ops->decrypt(&ksch->decr_ks.ks32[0], ksch->nr,
		    /* LINTED:  pointer alignment */
		    (uint32_t *)ct, (uint32_t *)pt);
	} else {
		uint32_t buffer[AES_BLOCK_LEN / sizeof (uint32_t)];

		/* Copy input block into buffer */
		if (ops->needs_byteswap) {
			buffer[0] = htonl(*(uint32_t *)(void *)&ct[0]);
			buffer[1] = htonl(*(uint32_t *)(void *)&ct[4]);
			buffer[2] = htonl(*(uint32_t *)(void *)&ct[8]);
			buffer[3] = htonl(*(uint32_t *)(void *)&ct[12]);
		} else
			bcopy(ct, &buffer, AES_BLOCK_LEN);

		ops->decrypt(&ksch->decr_ks.ks32[0], ksch->nr, buffer, buffer);

		/* Copy result from buffer to output block */
		if (ops->needs_byteswap) {
			*(uint32_t *)(void *)&pt[0] = htonl(buffer[0]);
			*(uint32_t *)(void *)&pt[4] = htonl(buffer[1]);
			*(uint32_t *)(void *)&pt[8] = htonl(buffer[2]);
			*(uint32_t *)(void *)&pt[12] = htonl(buffer[3]);
		} else
			bcopy(&buffer, pt, AES_BLOCK_LEN);
	}
	return (CRYPTO_SUCCESS);
}