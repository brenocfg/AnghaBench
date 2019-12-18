#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/ * lua_CFunction ;
struct TYPE_5__ {int /*<<< orphan*/  pt; int /*<<< orphan*/  sb; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_1__ BCWriteCtx ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcwrite_footer (TYPE_1__*) ; 
 int /*<<< orphan*/  bcwrite_header (TYPE_1__*) ; 
 int /*<<< orphan*/  bcwrite_proto (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_buf_need (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static TValue *cpwriter(lua_State *L, lua_CFunction dummy, void *ud)
{
  BCWriteCtx *ctx = (BCWriteCtx *)ud;
  UNUSED(L); UNUSED(dummy);
  lj_buf_need(&ctx->sb, 1024);  /* Avoids resize for most prototypes. */
  bcwrite_header(ctx);
  bcwrite_proto(ctx, ctx->pt);
  bcwrite_footer(ctx);
  return NULL;
}