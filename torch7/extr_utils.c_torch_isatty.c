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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_FILEHANDLE ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int torch_isatty(lua_State *L)
{
  FILE **fp = (FILE **) luaL_checkudata(L, -1, LUA_FILEHANDLE);
#ifdef _WIN32
  lua_pushboolean(L, _isatty(_fileno(*fp)));
#else
  lua_pushboolean(L, isatty(fileno(*fp)));
#endif
  return 1;
}