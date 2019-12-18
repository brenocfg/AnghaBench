#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ lua_Number ;
typedef  scalar_t__ int32_t ;
struct TYPE_4__ {scalar_t__ hi; } ;
struct TYPE_5__ {TYPE_1__ u32; } ;
typedef  TYPE_2__ TValue ;

/* Variables and functions */
 scalar_t__ lj_num2int (scalar_t__) ; 
 int /*<<< orphan*/  setnumV (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static int numistrueint(lua_Number n, int32_t *kp)
{
  int32_t k = lj_num2int(n);
  if (n == (lua_Number)k) {
    if (kp) *kp = k;
    if (k == 0) {  /* Special check for -0. */
      TValue tv;
      setnumV(&tv, n);
      if (tv.u32.hi != 0)
	return 0;
    }
    return 1;
  }
  return 0;
}