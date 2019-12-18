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
 int LUA_MAXINPUT ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stdin ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  write_prompt (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pushline(lua_State *L, int firstline)
{
  char buf[LUA_MAXINPUT];
  write_prompt(L, firstline);
  if (fgets(buf, LUA_MAXINPUT, stdin)) {
    size_t len = strlen(buf);
    if (len > 0 && buf[len-1] == '\n')
      buf[len-1] = '\0';
    if (firstline && buf[0] == '=')
      lua_pushfstring(L, "return %s", buf+1);
    else
      lua_pushstring(L, buf);
    return 1;
  }
  return 0;
}