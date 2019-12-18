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
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ BuildCtx ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void printhash(BuildCtx *ctx, uint32_t *htab, uint32_t sz)
{
  uint32_t i;
  fprintf(ctx->fp, "static const uint32_t fold_hash[%d] = {\n0x%08x",
	  sz+1, htab[0]);
  for (i = 1; i < sz+1; i++)
    fprintf(ctx->fp, ",\n0x%08x", htab[i]);
  fprintf(ctx->fp, "\n};\n\n");
}