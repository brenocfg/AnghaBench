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
typedef  scalar_t__ lua_Integer ;

/* Variables and functions */
 scalar_t__ luaL_optinteger (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static size_t initposition (lua_State *L, size_t len) {
  lua_Integer ii = luaL_optinteger(L, 3, 1);
  if (ii > 0) {  /* positive index? */
    if ((size_t)ii <= len)  /* inside the string? */
      return (size_t)ii - 1;  /* return it (corrected to 0-base) */
    else return len;  /* crop at the end */
  }
  else {  /* negative index */
    if ((size_t)(-ii) <= len)  /* inside the string? */
      return len - ((size_t)(-ii));  /* return position from the end */
    else return 0;  /* crop at the beginning */
  }
}