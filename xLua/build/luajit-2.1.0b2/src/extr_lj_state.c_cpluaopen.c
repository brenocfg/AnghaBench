#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  env; } ;
typedef  TYPE_2__ lua_State ;
typedef  void* lua_CFunction ;
struct TYPE_17__ {int threshold; int total; } ;
struct TYPE_19__ {TYPE_1__ gc; } ;
typedef  TYPE_3__ global_State ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 TYPE_3__* G (TYPE_2__*) ; 
 int /*<<< orphan*/  LJ_ERR_ERRMEM ; 
 int /*<<< orphan*/  LJ_MIN_GLOBAL ; 
 int /*<<< orphan*/  LJ_MIN_REGISTRY ; 
 scalar_t__ LJ_MIN_STRTAB ; 
 int /*<<< orphan*/  UNUSED (void*) ; 
 int /*<<< orphan*/  fixstring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_err_str (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_lex_init (TYPE_2__*) ; 
 int /*<<< orphan*/  lj_meta_init (TYPE_2__*) ; 
 int /*<<< orphan*/  lj_str_resize (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  lj_tab_new (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_trace_initstate (TYPE_3__*) ; 
 int /*<<< orphan*/  obj2gco (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  registry (TYPE_2__*) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  settabV (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_init (TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static TValue *cpluaopen(lua_State *L, lua_CFunction dummy, void *ud)
{
  global_State *g = G(L);
  UNUSED(dummy);
  UNUSED(ud);
  stack_init(L, L);
  /* NOBARRIER: State initialization, all objects are white. */
  setgcref(L->env, obj2gco(lj_tab_new(L, 0, LJ_MIN_GLOBAL)));
  settabV(L, registry(L), lj_tab_new(L, 0, LJ_MIN_REGISTRY));
  lj_str_resize(L, LJ_MIN_STRTAB-1);
  lj_meta_init(L);
  lj_lex_init(L);
  fixstring(lj_err_str(L, LJ_ERR_ERRMEM));  /* Preallocate memory error msg. */
  g->gc.threshold = 4*g->gc.total;
  lj_trace_initstate(g);
  return NULL;
}