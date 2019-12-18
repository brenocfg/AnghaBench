#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_ERR_OSDATEF ; 
 int /*<<< orphan*/  lj_err_callerv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char const*) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int getfield(lua_State *L, const char *key, int d)
{
  int res;
  lua_getfield(L, -1, key);
  if (lua_isnumber(L, -1)) {
    res = (int)lua_tointeger(L, -1);
  } else {
    if (d < 0)
      lj_err_callerv(L, LJ_ERR_OSDATEF, key);
    res = d;
  }
  lua_pop(L, 1);
  return res;
}