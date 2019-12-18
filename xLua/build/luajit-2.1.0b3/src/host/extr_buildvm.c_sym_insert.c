#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ptrdiff_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_6__ {TYPE_1__* sym; int /*<<< orphan*/  nsym; } ;
struct TYPE_5__ {scalar_t__ ofs; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ BuildCtx ;

/* Variables and functions */
 int /*<<< orphan*/  sym_decorate (TYPE_2__*,char const*,char const*) ; 

__attribute__((used)) static void sym_insert(BuildCtx *ctx, int32_t ofs,
		       const char *prefix, const char *suffix)
{
  ptrdiff_t i = ctx->nsym++;
  while (i > 0) {
    if (ctx->sym[i-1].ofs <= ofs)
      break;
    ctx->sym[i] = ctx->sym[i-1];
    i--;
  }
  ctx->sym[i].ofs = ofs;
  ctx->sym[i].name = sym_decorate(ctx, prefix, suffix);
}