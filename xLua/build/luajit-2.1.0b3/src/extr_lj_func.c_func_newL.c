#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {int /*<<< orphan*/  env; int /*<<< orphan*/  pc; scalar_t__ nupvalues; int /*<<< orphan*/  ffid; int /*<<< orphan*/  gct; } ;
struct TYPE_9__ {TYPE_1__ l; } ;
struct TYPE_8__ {scalar_t__ flags; scalar_t__ sizeuv; } ;
typedef  int /*<<< orphan*/  MSize ;
typedef  int /*<<< orphan*/  GCtab ;
typedef  TYPE_2__ GCproto ;
typedef  TYPE_3__ GCfunc ;

/* Variables and functions */
 int /*<<< orphan*/  FF_LUA ; 
 int /*<<< orphan*/  LJ_TFUNC ; 
 int PROTO_CLCOUNT ; 
 int PROTO_CLC_BITS ; 
 scalar_t__ lj_mem_newgco (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obj2gco (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proto_bc (TYPE_2__*) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setmref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizeLfunc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static GCfunc *func_newL(lua_State *L, GCproto *pt, GCtab *env)
{
  uint32_t count;
  GCfunc *fn = (GCfunc *)lj_mem_newgco(L, sizeLfunc((MSize)pt->sizeuv));
  fn->l.gct = ~LJ_TFUNC;
  fn->l.ffid = FF_LUA;
  fn->l.nupvalues = 0;  /* Set to zero until upvalues are initialized. */
  /* NOBARRIER: Really a setgcref. But the GCfunc is new (marked white). */
  setmref(fn->l.pc, proto_bc(pt));
  setgcref(fn->l.env, obj2gco(env));
  /* Saturating 3 bit counter (0..7) for created closures. */
  count = (uint32_t)pt->flags + PROTO_CLCOUNT;
  pt->flags = (uint8_t)(count - ((count >> PROTO_CLC_BITS) & PROTO_CLCOUNT));
  return fn;
}