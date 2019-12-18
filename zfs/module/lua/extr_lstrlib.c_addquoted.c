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
 scalar_t__ iscntrl (scalar_t__) ; 
 int /*<<< orphan*/  isdigit (scalar_t__) ; 
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,char const) ; 
 int /*<<< orphan*/  luaL_addstring (int /*<<< orphan*/ *,char*) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ uchar (char const) ; 

__attribute__((used)) static void addquoted (lua_State *L, luaL_Buffer *b, int arg) {
  size_t l;
  const char *s = luaL_checklstring(L, arg, &l);
  luaL_addchar(b, '"');
  while (l--) {
    if (*s == '"' || *s == '\\' || *s == '\n') {
      luaL_addchar(b, '\\');
      luaL_addchar(b, *s);
    }
    else if (*s == '\0' || iscntrl(uchar(*s))) {
      char buff[10];
      if (!isdigit(uchar(*(s+1))))
        sprintf(buff, "\\%d", (int)uchar(*s));
      else
        sprintf(buff, "\\%03d", (int)uchar(*s));
      luaL_addstring(b, buff);
    }
    else
      luaL_addchar(b, *s);
    s++;
  }
  luaL_addchar(b, '"');
}