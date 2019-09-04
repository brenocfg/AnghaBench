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
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 char* luaL_buffinitsize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_pushresultsize (int /*<<< orphan*/ *,size_t) ; 
 char tolower (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uchar (char const) ; 

__attribute__((used)) static int str_lower (lua_State *L) {
  size_t l;
  size_t i;
  luaL_Buffer b;
  const char *s = luaL_checklstring(L, 1, &l);
  char *p = luaL_buffinitsize(L, &b, l);
  for (i=0; i<l; i++)
    p[i] = tolower(uchar(s[i]));
  luaL_pushresultsize(&b, l);
  return 1;
}