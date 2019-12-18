#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_10__ {int /*<<< orphan*/  nkgc; int /*<<< orphan*/  kt; int /*<<< orphan*/ * L; } ;
struct TYPE_9__ {int /*<<< orphan*/  u64; } ;
typedef  TYPE_1__ TValue ;
typedef  int /*<<< orphan*/  GCobj ;
typedef  TYPE_2__ FuncState ;
typedef  int /*<<< orphan*/  BCReg ;

/* Variables and functions */
 TYPE_1__* lj_tab_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  setgcV (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ tvhaskslot (TYPE_1__*) ; 
 int /*<<< orphan*/  tvkslot (TYPE_1__*) ; 

__attribute__((used)) static BCReg const_gc(FuncState *fs, GCobj *gc, uint32_t itype)
{
  lua_State *L = fs->L;
  TValue key, *o;
  setgcV(L, &key, gc, itype);
  /* NOBARRIER: the key is new or kept alive. */
  o = lj_tab_set(L, fs->kt, &key);
  if (tvhaskslot(o))
    return tvkslot(o);
  o->u64 = fs->nkgc;
  return fs->nkgc++;
}