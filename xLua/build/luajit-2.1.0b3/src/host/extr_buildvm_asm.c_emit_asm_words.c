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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ BuildCtx ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int lj_bswap (int) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emit_asm_words(BuildCtx *ctx, uint8_t *p, int n)
{
  int i;
  for (i = 0; i < n; i += 4) {
    uint32_t ins = *(uint32_t *)(p+i);
#if LJ_TARGET_ARM64 && LJ_BE
    ins = lj_bswap(ins);  /* ARM64 instructions are always little-endian. */
#endif
    if ((i & 15) == 0)
      fprintf(ctx->fp, "\t.long 0x%08x", ins);
    else
      fprintf(ctx->fp, ",0x%08x", ins);
    if ((i & 15) == 12) putc('\n', ctx->fp);
  }
  if ((n & 15) != 0) putc('\n', ctx->fp);
}