#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  copyTV (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lj_lib_checkfunc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lj_lib_checkint (TYPE_1__*,int) ; 
 char* lua_getupvalue (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (TYPE_1__*,char const*) ; 
 char* lua_setupvalue (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int debug_getupvalue(lua_State *L, int get)
{
  int32_t n = lj_lib_checkint(L, 2);
  const char *name;
  lj_lib_checkfunc(L, 1);
  name = get ? lua_getupvalue(L, 1, n) : lua_setupvalue(L, 1, n);
  if (name) {
    lua_pushstring(L, name);
    if (!get) return 1;
    copyTV(L, L->top, L->top-2);
    L->top++;
    return 2;
  }
  return 0;
}