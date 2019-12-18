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
typedef  int /*<<< orphan*/  lua_Writer ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int strip; int status; int /*<<< orphan*/  sb; void* wdata; int /*<<< orphan*/  wfunc; int /*<<< orphan*/ * pt; } ;
typedef  int /*<<< orphan*/  GCproto ;
typedef  TYPE_1__ BCWriteCtx ;

/* Variables and functions */
 int /*<<< orphan*/  G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpwriter ; 
 int /*<<< orphan*/  lj_buf_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_buf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lj_vm_cpcall (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbufL (int /*<<< orphan*/ *) ; 

int lj_bcwrite(lua_State *L, GCproto *pt, lua_Writer writer, void *data,
	      int strip)
{
  BCWriteCtx ctx;
  int status;
  ctx.pt = pt;
  ctx.wfunc = writer;
  ctx.wdata = data;
  ctx.strip = strip;
  ctx.status = 0;
  lj_buf_init(L, &ctx.sb);
  status = lj_vm_cpcall(L, NULL, &ctx, cpwriter);
  if (status == 0) status = ctx.status;
  lj_buf_free(G(sbufL(&ctx.sb)), &ctx.sb);
  return status;
}