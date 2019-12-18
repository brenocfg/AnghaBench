#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t ptrdiff_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  global_State ;
struct TYPE_15__ {TYPE_3__* finalizer; } ;
struct TYPE_11__ {int /*<<< orphan*/  marked; } ;
struct TYPE_14__ {TYPE_1__ gch; } ;
struct TYPE_13__ {scalar_t__ hmask; int /*<<< orphan*/  metatable; int /*<<< orphan*/  node; } ;
struct TYPE_12__ {int /*<<< orphan*/  val; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_2__ Node ;
typedef  TYPE_3__ GCtab ;
typedef  TYPE_4__ GCobj ;
typedef  TYPE_5__ CTState ;

/* Variables and functions */
 int /*<<< orphan*/ * G (int /*<<< orphan*/ *) ; 
 scalar_t__ LJ_GC_CDATA_FIN ; 
 int /*<<< orphan*/  copyTV (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* ctype_ctsG (int /*<<< orphan*/ *) ; 
 TYPE_4__* gcV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gc_call_finalizer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  makewhite (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_2__* noderef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setgcrefnull (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setnilV (int /*<<< orphan*/ *) ; 
 scalar_t__ tviscdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvisnil (int /*<<< orphan*/ *) ; 

void lj_gc_finalize_cdata(lua_State *L)
{
  global_State *g = G(L);
  CTState *cts = ctype_ctsG(g);
  if (cts) {
    GCtab *t = cts->finalizer;
    Node *node = noderef(t->node);
    ptrdiff_t i;
    setgcrefnull(t->metatable);  /* Mark finalizer table as disabled. */
    for (i = (ptrdiff_t)t->hmask; i >= 0; i--)
      if (!tvisnil(&node[i].val) && tviscdata(&node[i].key)) {
	GCobj *o = gcV(&node[i].key);
	TValue tmp;
	makewhite(g, o);
	o->gch.marked &= (uint8_t)~LJ_GC_CDATA_FIN;
	copyTV(L, &tmp, &node[i].val);
	setnilV(&node[i].val);
	gc_call_finalizer(g, L, &tmp, o);
      }
  }
}