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
struct TYPE_8__ {scalar_t__ top; scalar_t__ base; } ;
typedef  TYPE_1__ lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_ERR_RDRSTR ; 
 int /*<<< orphan*/  UNUSED (void*) ; 
 int /*<<< orphan*/  copyTV (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lj_err_caller (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_checkstack (TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  lua_call (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 char const* lua_tolstring (TYPE_1__*,int,size_t*) ; 
 scalar_t__ tvisnil (scalar_t__) ; 
 scalar_t__ tvisnumber (scalar_t__) ; 
 scalar_t__ tvisstr (scalar_t__) ; 

__attribute__((used)) static const char *reader_func(lua_State *L, void *ud, size_t *size)
{
  UNUSED(ud);
  luaL_checkstack(L, 2, "too many nested functions");
  copyTV(L, L->top++, L->base);
  lua_call(L, 0, 1);  /* Call user-supplied function. */
  L->top--;
  if (tvisnil(L->top)) {
    *size = 0;
    return NULL;
  } else if (tvisstr(L->top) || tvisnumber(L->top)) {
    copyTV(L, L->base+4, L->top);  /* Anchor string in reserved stack slot. */
    return lua_tolstring(L, 5, size);
  } else {
    lj_err_caller(L, LJ_ERR_RDRSTR);
    return NULL;
  }
}