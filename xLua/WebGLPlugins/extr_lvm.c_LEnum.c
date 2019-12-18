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
typedef  int /*<<< orphan*/  lua_Number ;
typedef  scalar_t__ lua_Integer ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 int LEintfloat (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LTintfloat (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fltvalue (int /*<<< orphan*/  const*) ; 
 scalar_t__ ivalue (int /*<<< orphan*/  const*) ; 
 scalar_t__ luai_numisnan (int /*<<< orphan*/ ) ; 
 int luai_numle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ttisfloat (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisinteger (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int LEnum (const TValue *l, const TValue *r) {
  if (ttisinteger(l)) {
    lua_Integer li = ivalue(l);
    if (ttisinteger(r))
      return li <= ivalue(r);  /* both are integers */
    else  /* 'l' is int and 'r' is float */
      return LEintfloat(li, fltvalue(r));  /* l <= r ? */
  }
  else {
    lua_Number lf = fltvalue(l);  /* 'l' must be float */
    if (ttisfloat(r))
      return luai_numle(lf, fltvalue(r));  /* both are float */
    else if (luai_numisnan(lf))  /* 'r' is int and 'l' is float */
      return 0;  /*  NaN <= i is always false */
    else  /* without NaN, (l <= r)  <-->  not(r < l) */
      return !LTintfloat(ivalue(r), lf);  /* not (r < l) ? */
  }
}