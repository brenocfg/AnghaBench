#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_10__ {TYPE_1__* finalizer; } ;
struct TYPE_9__ {int /*<<< orphan*/  marked; } ;
struct TYPE_8__ {int /*<<< orphan*/  metatable; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_1__ GCtab ;
typedef  int /*<<< orphan*/  GCobj ;
typedef  TYPE_2__ GCcdata ;

/* Variables and functions */
 int /*<<< orphan*/  G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LJ_GC_CDATA_FIN ; 
 int /*<<< orphan*/  LJ_TNIL ; 
 TYPE_7__* ctype_ctsG (int /*<<< orphan*/ ) ; 
 scalar_t__ gcref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_gc_anybarriert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * lj_tab_set (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setcdataV (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  setgcV (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setnilV (int /*<<< orphan*/ *) ; 

void lj_cdata_setfin(lua_State *L, GCcdata *cd, GCobj *obj, uint32_t it)
{
  GCtab *t = ctype_ctsG(G(L))->finalizer;
  if (gcref(t->metatable)) {
    /* Add cdata to finalizer table, if still enabled. */
    TValue *tv, tmp;
    setcdataV(L, &tmp, cd);
    lj_gc_anybarriert(L, t);
    tv = lj_tab_set(L, t, &tmp);
    if (it == LJ_TNIL) {
      setnilV(tv);
      cd->marked &= ~LJ_GC_CDATA_FIN;
    } else {
      setgcV(L, tv, obj, it);
      cd->marked |= LJ_GC_CDATA_FIN;
    }
  }
}