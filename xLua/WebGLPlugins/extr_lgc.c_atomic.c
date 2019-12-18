#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  scalar_t__ l_mem ;
struct TYPE_15__ {int gcfinnum; scalar_t__ GCmemtrav; int /*<<< orphan*/  currentwhite; int /*<<< orphan*/ * allweak; int /*<<< orphan*/ * weak; int /*<<< orphan*/ * ephemeron; int /*<<< orphan*/ * gray; int /*<<< orphan*/  l_registry; int /*<<< orphan*/  gcstate; int /*<<< orphan*/  mainthread; int /*<<< orphan*/ * grayagain; } ;
typedef  TYPE_1__ global_State ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GCSinsideatomic ; 
 int /*<<< orphan*/  cast_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clearkeys (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clearvalues (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  convergeephemerons (TYPE_1__*) ; 
 int /*<<< orphan*/  iswhite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaS_clearcache (TYPE_1__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  markbeingfnz (TYPE_1__*) ; 
 int /*<<< orphan*/  markmt (TYPE_1__*) ; 
 int /*<<< orphan*/  markobject (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  markvalue (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  otherwhite (TYPE_1__*) ; 
 int /*<<< orphan*/  propagateall (TYPE_1__*) ; 
 int /*<<< orphan*/  remarkupvals (TYPE_1__*) ; 
 int /*<<< orphan*/  separatetobefnz (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static l_mem atomic (lua_State *L) {
  global_State *g = G(L);
  l_mem work;
  GCObject *origweak, *origall;
  GCObject *grayagain = g->grayagain;  /* save original list */
  lua_assert(g->ephemeron == NULL && g->weak == NULL);
  lua_assert(!iswhite(g->mainthread));
  g->gcstate = GCSinsideatomic;
  g->GCmemtrav = 0;  /* start counting work */
  markobject(g, L);  /* mark running thread */
  /* registry and global metatables may be changed by API */
  markvalue(g, &g->l_registry);
  markmt(g);  /* mark global metatables */
  /* remark occasional upvalues of (maybe) dead threads */
  remarkupvals(g);
  propagateall(g);  /* propagate changes */
  work = g->GCmemtrav;  /* stop counting (do not recount 'grayagain') */
  g->gray = grayagain;
  propagateall(g);  /* traverse 'grayagain' list */
  g->GCmemtrav = 0;  /* restart counting */
  convergeephemerons(g);
  /* at this point, all strongly accessible objects are marked. */
  /* Clear values from weak tables, before checking finalizers */
  clearvalues(g, g->weak, NULL);
  clearvalues(g, g->allweak, NULL);
  origweak = g->weak; origall = g->allweak;
  work += g->GCmemtrav;  /* stop counting (objects being finalized) */
  separatetobefnz(g, 0);  /* separate objects to be finalized */
  g->gcfinnum = 1;  /* there may be objects to be finalized */
  markbeingfnz(g);  /* mark objects that will be finalized */
  propagateall(g);  /* remark, to propagate 'resurrection' */
  g->GCmemtrav = 0;  /* restart counting */
  convergeephemerons(g);
  /* at this point, all resurrected objects are marked. */
  /* remove dead objects from weak tables */
  clearkeys(g, g->ephemeron, NULL);  /* clear keys from all ephemeron tables */
  clearkeys(g, g->allweak, NULL);  /* clear keys from all 'allweak' tables */
  /* clear values from resurrected weak tables */
  clearvalues(g, g->weak, origweak);
  clearvalues(g, g->allweak, origall);
  luaS_clearcache(g);
  g->currentwhite = cast_byte(otherwhite(g));  /* flip current white */
  work += g->GCmemtrav;  /* complete counting */
  return work;  /* estimate of memory marked by 'atomic' */
}