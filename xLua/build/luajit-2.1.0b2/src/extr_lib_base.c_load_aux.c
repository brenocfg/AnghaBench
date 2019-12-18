#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ top; scalar_t__ base; } ;
typedef  TYPE_2__ lua_State ;
struct TYPE_8__ {int /*<<< orphan*/  env; } ;
struct TYPE_10__ {TYPE_1__ c; } ;
typedef  int /*<<< orphan*/  GCtab ;
typedef  TYPE_3__ GCfunc ;

/* Variables and functions */
 TYPE_3__* funcV (scalar_t__) ; 
 int /*<<< orphan*/  lj_gc_objbarrier (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obj2gco (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setnilV (scalar_t__) ; 
 int /*<<< orphan*/ * tabV (scalar_t__) ; 
 scalar_t__ tvistab (scalar_t__) ; 

__attribute__((used)) static int load_aux(lua_State *L, int status, int envarg)
{
  if (status == 0) {
    if (tvistab(L->base+envarg-1)) {
      GCfunc *fn = funcV(L->top-1);
      GCtab *t = tabV(L->base+envarg-1);
      setgcref(fn->c.env, obj2gco(t));
      lj_gc_objbarrier(L, fn, t);
    }
    return 1;
  } else {
    setnilV(L->top-2);
    return 2;
  }
}