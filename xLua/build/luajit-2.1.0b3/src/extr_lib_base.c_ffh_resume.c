#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ status; scalar_t__ top; scalar_t__ base; int /*<<< orphan*/ * cframe; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  MSize ;
typedef  int /*<<< orphan*/  ErrMsg ;

/* Variables and functions */
 int FFH_RES (int) ; 
 int FFH_RETRY ; 
 int /*<<< orphan*/  LJ_ERR_CODEAD ; 
 int /*<<< orphan*/  LJ_ERR_CORUN ; 
 int LJ_FR2 ; 
 scalar_t__ LUA_OK ; 
 scalar_t__ LUA_YIELD ; 
 int /*<<< orphan*/  lj_err_caller (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_err_str (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_state_growstack (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setboolV (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setstrV (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ffh_resume(lua_State *L, lua_State *co, int wrap)
{
  if (co->cframe != NULL || co->status > LUA_YIELD ||
      (co->status == LUA_OK && co->top == co->base)) {
    ErrMsg em = co->cframe ? LJ_ERR_CORUN : LJ_ERR_CODEAD;
    if (wrap) lj_err_caller(L, em);
    setboolV(L->base-1-LJ_FR2, 0);
    setstrV(L, L->base-LJ_FR2, lj_err_str(L, em));
    return FFH_RES(2);
  }
  lj_state_growstack(co, (MSize)(L->top - L->base));
  return FFH_RETRY;
}