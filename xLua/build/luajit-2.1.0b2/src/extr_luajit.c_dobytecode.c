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
 scalar_t__ loadjitmodule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pcall (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int report (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dobytecode(lua_State *L, char **argv)
{
  int narg = 0;
  lua_pushliteral(L, "bcsave");
  if (loadjitmodule(L))
    return 1;
  if (argv[0][2]) {
    narg++;
    argv[0][1] = '-';
    lua_pushstring(L, argv[0]+1);
  }
  for (argv++; *argv != NULL; narg++, argv++)
    lua_pushstring(L, *argv);
  return report(L, lua_pcall(L, narg, 0, 0));
}