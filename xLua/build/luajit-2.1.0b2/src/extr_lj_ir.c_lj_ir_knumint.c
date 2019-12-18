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
typedef  int /*<<< orphan*/  jit_State ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  TRef ;

/* Variables and functions */
 int /*<<< orphan*/  lj_ir_kint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_knum (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ numistrueint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

TRef lj_ir_knumint(jit_State *J, lua_Number n)
{
  int32_t k;
  if (numistrueint(n, &k))
    return lj_ir_kint(J, k);
  else
    return lj_ir_knum(J, n);
}