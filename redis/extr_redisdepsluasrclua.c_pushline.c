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
 char* get_prompt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_freeline (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_readline (int /*<<< orphan*/ *,char*,char const*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int pushline (lua_State *L, int firstline) {
  char buffer[LUA_MAXINPUT];
  char *b = buffer;
  size_t l;
  const char *prmt = get_prompt(L, firstline);
  if (lua_readline(L, b, prmt) == 0)
    return 0;  /* no input */
  l = strlen(b);
  if (l > 0 && b[l-1] == '\n')  /* line ends with newline? */
    b[l-1] = '\0';  /* remove it */
  if (firstline && b[0] == '=')  /* first line starts with `=' ? */
    lua_pushfstring(L, "return %s", b+1);  /* change it to `return' */
  else
    lua_pushstring(L, b);
  lua_freeline(L, b);
  return 1;
}