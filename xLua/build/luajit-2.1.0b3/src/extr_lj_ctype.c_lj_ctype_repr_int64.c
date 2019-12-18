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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  GCstr ;

/* Variables and functions */
 int /*<<< orphan*/ * lj_str_new (int /*<<< orphan*/ *,char*,size_t) ; 

GCstr *lj_ctype_repr_int64(lua_State *L, uint64_t n, int isunsigned)
{
  char buf[1+20+3];
  char *p = buf+sizeof(buf);
  int sign = 0;
  *--p = 'L'; *--p = 'L';
  if (isunsigned) {
    *--p = 'U';
  } else if ((int64_t)n < 0) {
    n = (uint64_t)-(int64_t)n;
    sign = 1;
  }
  do { *--p = (char)('0' + n % 10); } while (n /= 10);
  if (sign) *--p = '-';
  return lj_str_new(L, p, (size_t)(buf+sizeof(buf)-p));
}