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
struct TYPE_3__ {int mode; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ BuildCtx ;

/* Variables and functions */
#define  BUILD_coffasm 130 
#define  BUILD_elfasm 129 
#define  BUILD_machasm 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void emit_asm_align(BuildCtx *ctx, int bits)
{
  switch (ctx->mode) {
  case BUILD_elfasm:
  case BUILD_coffasm:
    fprintf(ctx->fp, "\t.p2align %d\n", bits);
    break;
  case BUILD_machasm:
    fprintf(ctx->fp, "\t.align %d\n", bits);
    break;
  default:
    break;
  }
}