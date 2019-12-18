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
typedef  int /*<<< orphan*/  zio_cksum_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ctx ;
typedef  int /*<<< orphan*/  abd_t ;
typedef  int /*<<< orphan*/  Skein_512_Ctxt_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Skein_512_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abd_iterate_func (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcopy (void const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skein_incremental ; 

void
abd_checksum_skein_native(abd_t *abd, uint64_t size,
    const void *ctx_template, zio_cksum_t *zcp)
{
	Skein_512_Ctxt_t	ctx;

	ASSERT(ctx_template != NULL);
	bcopy(ctx_template, &ctx, sizeof (ctx));
	(void) abd_iterate_func(abd, 0, size, skein_incremental, &ctx);
	(void) Skein_512_Final(&ctx, (uint8_t *)zcp);
	bzero(&ctx, sizeof (ctx));
}