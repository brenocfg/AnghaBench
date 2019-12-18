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
struct sha256_ctx {int buflen; int total64; int* total; int* H; int /*<<< orphan*/ * buffer; void** buffer32; } ;
typedef  int UINTN ;
typedef  int UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  CopyMem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* SWAP (int) ; 
 size_t TOTAL64_high ; 
 size_t TOTAL64_low ; 
 int /*<<< orphan*/  fillbuf ; 
 int /*<<< orphan*/  sha256_process_block (int /*<<< orphan*/ *,int,struct sha256_ctx*) ; 

void *sha256_finish_ctx(struct sha256_ctx *ctx, void *resbuf) {
        /* Take yet unprocessed bytes into account.  */
        UINT32 bytes = ctx->buflen;
        UINTN pad, i;

        /* Now count remaining bytes.  */
        ctx->total64 += bytes;

        pad = bytes >= 56 ? 64 + 56 - bytes : 56 - bytes;
        CopyMem (&ctx->buffer[bytes], fillbuf, pad);

        /* Put the 64-bit file length in *bits* at the end of the buffer.  */
        ctx->buffer32[(bytes + pad + 4) / 4] = SWAP (ctx->total[TOTAL64_low] << 3);
        ctx->buffer32[(bytes + pad) / 4] = SWAP ((ctx->total[TOTAL64_high] << 3)
                                                 | (ctx->total[TOTAL64_low] >> 29));

        /* Process last bytes.  */
        sha256_process_block (ctx->buffer, bytes + pad + 8, ctx);

        /* Put result from CTX in first 32 bytes following RESBUF.  */
        for (i = 0; i < 8; ++i)
                ((UINT32 *) resbuf)[i] = SWAP (ctx->H[i]);

        return resbuf;
}