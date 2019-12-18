#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_17__ {int /*<<< orphan*/  (* panic ) (TYPE_1__*) ;} ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 TYPE_9__* G (TYPE_1__*) ; 
 int /*<<< orphan*/  KEY_PROFILE_FUNC ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  funcV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_str_new (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/ * lj_tab_get (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_trace_abort (TYPE_9__*) ; 
 int lua_pcall (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  registry (TYPE_1__*) ; 
 int /*<<< orphan*/  setfuncV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setintV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setlightudV (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  setstrV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setthreadV (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  tabV (int /*<<< orphan*/ ) ; 
 scalar_t__ tvisfunc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jit_profile_callback(lua_State *L2, lua_State *L, int samples,
				 int vmstate)
{
  TValue key;
  cTValue *tv;
  setlightudV(&key, (void *)&KEY_PROFILE_FUNC);
  tv = lj_tab_get(L, tabV(registry(L)), &key);
  if (tvisfunc(tv)) {
    char vmst = (char)vmstate;
    int status;
    setfuncV(L2, L2->top++, funcV(tv));
    setthreadV(L2, L2->top++, L);
    setintV(L2->top++, samples);
    setstrV(L2, L2->top++, lj_str_new(L2, &vmst, 1));
    status = lua_pcall(L2, 3, 0, 0);  /* callback(thread, samples, vmstate) */
    if (status) {
      if (G(L2)->panic) G(L2)->panic(L2);
      exit(EXIT_FAILURE);
    }
    lj_trace_abort(G(L2));
  }
}