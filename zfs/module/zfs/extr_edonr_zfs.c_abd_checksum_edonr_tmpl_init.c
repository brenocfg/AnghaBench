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
struct TYPE_3__ {int /*<<< orphan*/ * zcs_bytes; } ;
typedef  TYPE_1__ zio_cksum_salt_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  salt_block ;
typedef  void EdonRState ;

/* Variables and functions */
 int /*<<< orphan*/  CTASSERT (int) ; 
 int EDONR_BLOCK_SIZE ; 
 int EDONR_MODE ; 
 int /*<<< orphan*/  EdonRHash (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EdonRInit (void*,int) ; 
 int /*<<< orphan*/  EdonRUpdate (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 void* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

void *
abd_checksum_edonr_tmpl_init(const zio_cksum_salt_t *salt)
{
	EdonRState	*ctx;
	uint8_t		salt_block[EDONR_BLOCK_SIZE];

	/*
	 * Edon-R needs all but the last hash invocation to be on full-size
	 * blocks, but the salt is too small. Rather than simply padding it
	 * with zeros, we expand the salt into a new salt block of proper
	 * size by double-hashing it (the new salt block will be composed of
	 * H(salt) || H(H(salt))).
	 */
	CTASSERT(EDONR_BLOCK_SIZE == 2 * (EDONR_MODE / 8));
	EdonRHash(EDONR_MODE, salt->zcs_bytes, sizeof (salt->zcs_bytes) * 8,
	    salt_block);
	EdonRHash(EDONR_MODE, salt_block, EDONR_MODE, salt_block +
	    EDONR_MODE / 8);

	/*
	 * Feed the new salt block into the hash function - this will serve
	 * as our MAC key.
	 */
	ctx = kmem_zalloc(sizeof (*ctx), KM_SLEEP);
	EdonRInit(ctx, EDONR_MODE);
	EdonRUpdate(ctx, salt_block, sizeof (salt_block) * 8);
	return (ctx);
}