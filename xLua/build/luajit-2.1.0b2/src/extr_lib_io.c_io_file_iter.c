#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ base; scalar_t__ top; } ;
typedef  TYPE_2__ lua_State ;
struct TYPE_15__ {int nupvalues; int /*<<< orphan*/ * upvalue; } ;
struct TYPE_18__ {TYPE_1__ c; } ;
struct TYPE_17__ {int type; int /*<<< orphan*/ * fp; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  MSize ;
typedef  TYPE_3__ IOFileUD ;
typedef  TYPE_4__ GCfunc ;

/* Variables and functions */
 int IOFILE_FLAG_CLOSE ; 
 int /*<<< orphan*/  LJ_ERR_IOCLFL ; 
 int /*<<< orphan*/  LJ_ERR_STKOV ; 
 int LUAI_MAXCSTACK ; 
 TYPE_4__* curr_func (TYPE_2__*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_file_close (TYPE_2__*,TYPE_3__*) ; 
 int io_file_read (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_err_caller (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_err_callermsg (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_state_checkstack (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strVdata (scalar_t__) ; 
 scalar_t__ tvisnil (scalar_t__) ; 
 int /*<<< orphan*/  udataV (int /*<<< orphan*/ *) ; 
 TYPE_3__* uddata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int io_file_iter(lua_State *L)
{
  GCfunc *fn = curr_func(L);
  IOFileUD *iof = uddata(udataV(&fn->c.upvalue[0]));
  int n = fn->c.nupvalues - 1;
  if (iof->fp == NULL)
    lj_err_caller(L, LJ_ERR_IOCLFL);
  L->top = L->base;
  if (n) {  /* Copy upvalues with options to stack. */
    if (n > LUAI_MAXCSTACK)
      lj_err_caller(L, LJ_ERR_STKOV);
    lj_state_checkstack(L, (MSize)n);
    memcpy(L->top, &fn->c.upvalue[1], n*sizeof(TValue));
    L->top += n;
  }
  n = io_file_read(L, iof->fp, 0);
  if (ferror(iof->fp))
    lj_err_callermsg(L, strVdata(L->top-2));
  if (tvisnil(L->base) && (iof->type & IOFILE_FLAG_CLOSE)) {
    io_file_close(L, iof);  /* Return values are ignored. */
    return 0;
  }
  return n;
}