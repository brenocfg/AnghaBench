#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  X ;
struct TYPE_7__ {size_t bCnt; int hashBitLen; int /*<<< orphan*/ * T; } ;
struct TYPE_6__ {int /*<<< orphan*/ * X; TYPE_3__ h; int /*<<< orphan*/ * b; } ;
typedef  TYPE_1__ Skein_256_Ctxt_t ;

/* Variables and functions */
 int /*<<< orphan*/  OUT_FINAL ; 
 size_t SKEIN_256_BLOCK_BYTES ; 
 int SKEIN_256_STATE_WORDS ; 
 int /*<<< orphan*/  SKEIN_FAIL ; 
 int SKEIN_SUCCESS ; 
 int /*<<< orphan*/  SKEIN_T1_FLAG_FINAL ; 
 int /*<<< orphan*/  Skein_256_Process_Block (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  Skein_Assert (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Skein_Put64_LSB_First (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  Skein_Show_Final (int,TYPE_3__*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Skein_Start_New_Type (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Skein_Swap64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

int
Skein_256_Final(Skein_256_Ctxt_t *ctx, uint8_t *hashVal)
{
	size_t i, n, byteCnt;
	uint64_t X[SKEIN_256_STATE_WORDS];

	/* catch uninitialized context */
	Skein_Assert(ctx->h.bCnt <= SKEIN_256_BLOCK_BYTES, SKEIN_FAIL);

	ctx->h.T[1] |= SKEIN_T1_FLAG_FINAL;	/* tag as the final block */
	/* zero pad b[] if necessary */
	if (ctx->h.bCnt < SKEIN_256_BLOCK_BYTES)
		bzero(&ctx->b[ctx->h.bCnt],
		    SKEIN_256_BLOCK_BYTES - ctx->h.bCnt);

	/* process the final block */
	Skein_256_Process_Block(ctx, ctx->b, 1, ctx->h.bCnt);

	/* now output the result */
	/* total number of output bytes */
	byteCnt = (ctx->h.hashBitLen + 7) >> 3;

	/* run Threefish in "counter mode" to generate output */
	/* zero out b[], so it can hold the counter */
	bzero(ctx->b, sizeof (ctx->b));
	/* keep a local copy of counter mode "key" */
	bcopy(ctx->X, X, sizeof (X));
	for (i = 0; i * SKEIN_256_BLOCK_BYTES < byteCnt; i++) {
		/* build the counter block */
		uint64_t tmp = Skein_Swap64((uint64_t)i);
		bcopy(&tmp, ctx->b, sizeof (tmp));
		Skein_Start_New_Type(ctx, OUT_FINAL);
		/* run "counter mode" */
		Skein_256_Process_Block(ctx, ctx->b, 1, sizeof (uint64_t));
		/* number of output bytes left to go */
		n = byteCnt - i * SKEIN_256_BLOCK_BYTES;
		if (n >= SKEIN_256_BLOCK_BYTES)
			n = SKEIN_256_BLOCK_BYTES;
		Skein_Put64_LSB_First(hashVal + i * SKEIN_256_BLOCK_BYTES,
		    ctx->X, n);	/* "output" the ctr mode bytes */
		Skein_Show_Final(256, &ctx->h, n,
		    hashVal + i * SKEIN_256_BLOCK_BYTES);
		/* restore the counter mode key for next time */
		bcopy(X, ctx->X, sizeof (X));
	}
	return (SKEIN_SUCCESS);
}