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
typedef  scalar_t__ lua_Number ;
typedef  int /*<<< orphan*/  lua_Integer ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 scalar_t__ cvt2num (int /*<<< orphan*/  const*) ; 
 scalar_t__ fltvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ivalue (int /*<<< orphan*/  const*) ; 
 scalar_t__ l_floor (scalar_t__) ; 
 scalar_t__ luaO_str2num (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int lua_numbertointeger (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svalue (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisfloat (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisinteger (int /*<<< orphan*/  const*) ; 
 scalar_t__ vslen (int /*<<< orphan*/  const*) ; 

int luaV_tointeger (const TValue *obj, lua_Integer *p, int mode) {
  TValue v;
 again:
  if (ttisfloat(obj)) {
    lua_Number n = fltvalue(obj);
    lua_Number f = l_floor(n);
    if (n != f) {  /* not an integral value? */
      if (mode == 0) return 0;  /* fails if mode demands integral value */
      else if (mode > 1)  /* needs ceil? */
        f += 1;  /* convert floor to ceil (remember: n != f) */
    }
    return lua_numbertointeger(f, p);
  }
  else if (ttisinteger(obj)) {
    *p = ivalue(obj);
    return 1;
  }
  else if (cvt2num(obj) &&
            luaO_str2num(svalue(obj), &v) == vslen(obj) + 1) {
    obj = &v;
    goto again;  /* convert result from 'luaO_str2num' to an integer */
  }
  return 0;  /* conversion failed */
}