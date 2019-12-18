#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_19__ {int /*<<< orphan*/  weak; } ;
struct TYPE_20__ {TYPE_1__ gc; } ;
typedef  TYPE_2__ global_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_23__ {TYPE_4__* finalizer; } ;
struct TYPE_22__ {int marked; scalar_t__ asize; scalar_t__ hmask; int /*<<< orphan*/  node; int /*<<< orphan*/  gclist; int /*<<< orphan*/  metatable; } ;
struct TYPE_21__ {int /*<<< orphan*/  val; int /*<<< orphan*/  key; } ;
typedef  TYPE_3__ Node ;
typedef  scalar_t__ MSize ;
typedef  TYPE_4__ GCtab ;
typedef  TYPE_5__ CTState ;

/* Variables and functions */
 int LJ_GC_WEAK ; 
 int LJ_GC_WEAKKEY ; 
 int LJ_GC_WEAKVAL ; 
 int /*<<< orphan*/  MM_mode ; 
 int /*<<< orphan*/ * arrayslot (TYPE_4__*,scalar_t__) ; 
 TYPE_5__* ctype_ctsG (TYPE_2__*) ; 
 int /*<<< orphan*/  gc_markobj (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  gc_marktv (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lj_meta_fastg (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 TYPE_3__* noderef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obj2gco (TYPE_4__*) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setgcrefr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strVdata (int /*<<< orphan*/ *) ; 
 TYPE_4__* tabref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvisnil (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisstr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gc_traverse_tab(global_State *g, GCtab *t)
{
  int weak = 0;
  cTValue *mode;
  GCtab *mt = tabref(t->metatable);
  if (mt)
    gc_markobj(g, mt);
  mode = lj_meta_fastg(g, mt, MM_mode);
  if (mode && tvisstr(mode)) {  /* Valid __mode field? */
    const char *modestr = strVdata(mode);
    int c;
    while ((c = *modestr++)) {
      if (c == 'k') weak |= LJ_GC_WEAKKEY;
      else if (c == 'v') weak |= LJ_GC_WEAKVAL;
    }
    if (weak) {  /* Weak tables are cleared in the atomic phase. */
#if LJ_HASFFI
      CTState *cts = ctype_ctsG(g);
      if (cts && cts->finalizer == t) {
	weak = (int)(~0u & ~LJ_GC_WEAKVAL);
      } else
#endif
      {
	t->marked = (uint8_t)((t->marked & ~LJ_GC_WEAK) | weak);
	setgcrefr(t->gclist, g->gc.weak);
	setgcref(g->gc.weak, obj2gco(t));
      }
    }
  }
  if (weak == LJ_GC_WEAK)  /* Nothing to mark if both keys/values are weak. */
    return 1;
  if (!(weak & LJ_GC_WEAKVAL)) {  /* Mark array part. */
    MSize i, asize = t->asize;
    for (i = 0; i < asize; i++)
      gc_marktv(g, arrayslot(t, i));
  }
  if (t->hmask > 0) {  /* Mark hash part. */
    Node *node = noderef(t->node);
    MSize i, hmask = t->hmask;
    for (i = 0; i <= hmask; i++) {
      Node *n = &node[i];
      if (!tvisnil(&n->val)) {  /* Mark non-empty slot. */
	lua_assert(!tvisnil(&n->key));
	if (!(weak & LJ_GC_WEAKKEY)) gc_marktv(g, &n->key);
	if (!(weak & LJ_GC_WEAKVAL)) gc_marktv(g, &n->val);
      }
    }
  }
  return weak;
}