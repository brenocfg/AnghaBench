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
typedef  int /*<<< orphan*/  Header ;

/* Variables and functions */
 int /*<<< orphan*/  controloptions (int /*<<< orphan*/ *,int,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  defaultoptions (int /*<<< orphan*/ *) ; 
 scalar_t__ gettoalign (size_t,int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  isalnum (int) ; 
 int /*<<< orphan*/  luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,size_t) ; 
 size_t optsize (int /*<<< orphan*/ *,int,char const**) ; 

__attribute__((used)) static int b_size (lua_State *L) {
  Header h;
  const char *fmt = luaL_checkstring(L, 1);
  size_t pos = 0;
  defaultoptions(&h);
  while (*fmt) {
    int opt = *fmt++;
    size_t size = optsize(L, opt, &fmt);
    pos += gettoalign(pos, &h, opt, size);
    if (opt == 's')
      luaL_argerror(L, 1, "option 's' has no fixed size");
    else if (opt == 'c' && size == 0)
      luaL_argerror(L, 1, "option 'c0' has no fixed size");
    if (!isalnum(opt))
      controloptions(L, opt, &fmt, &h);
    pos += size;
  }
  lua_pushinteger(L, pos);
  return 1;
}