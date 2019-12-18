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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_6__ {size_t nreloc; scalar_t__ nrelocsym; int /*<<< orphan*/ * code; TYPE_1__* reloc; int /*<<< orphan*/ * relocsym; } ;
struct TYPE_5__ {int type; scalar_t__ sym; scalar_t__ ofs; } ;
typedef  TYPE_2__ BuildCtx ;

/* Variables and functions */
 size_t BUILD_MAX_RELOC ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * extnames ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__* relocmap ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  sym_decorate (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int collect_reloc(BuildCtx *ctx, uint8_t *addr, int idx, int type)
{
  if (ctx->nreloc >= BUILD_MAX_RELOC) {
    fprintf(stderr, "Error: too many relocations, increase BUILD_MAX_RELOC.\n");
    exit(1);
  }
  if (relocmap[idx] < 0) {
    relocmap[idx] = ctx->nrelocsym;
    ctx->relocsym[ctx->nrelocsym] = sym_decorate(ctx, "", extnames[idx]);
    ctx->nrelocsym++;
  }
  ctx->reloc[ctx->nreloc].ofs = (int32_t)(addr - ctx->code);
  ctx->reloc[ctx->nreloc].sym = relocmap[idx];
  ctx->reloc[ctx->nreloc].type = type;
  ctx->nreloc++;
#if LJ_TARGET_XBOX360
  return (int)(ctx->code - addr) + 4;  /* Encode symbol offset of .text. */
#else
  return 0;  /* Encode symbol offset of 0. */
#endif
}