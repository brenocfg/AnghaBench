#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ lua_Number ;
typedef  scalar_t__ int32_t ;
struct TYPE_7__ {int /*<<< orphan*/  nval; } ;
struct TYPE_8__ {TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_2__ ExpDesc ;
typedef  scalar_t__ BinOpr ;

/* Variables and functions */
 scalar_t__ LJ_DUALNUM ; 
 scalar_t__ OPR_ADD ; 
 int /*<<< orphan*/  expr_isnumk_nojump (TYPE_2__*) ; 
 int /*<<< orphan*/  expr_numberV (TYPE_2__*) ; 
 scalar_t__ lj_num2int (scalar_t__) ; 
 scalar_t__ lj_vm_foldarith (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  setintV (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  setnumV (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ tvismzero (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnan (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int foldarith(BinOpr opr, ExpDesc *e1, ExpDesc *e2)
{
  TValue o;
  lua_Number n;
  if (!expr_isnumk_nojump(e1) || !expr_isnumk_nojump(e2)) return 0;
  n = lj_vm_foldarith(expr_numberV(e1), expr_numberV(e2), (int)opr-OPR_ADD);
  setnumV(&o, n);
  if (tvisnan(&o) || tvismzero(&o)) return 0;  /* Avoid NaN and -0 as consts. */
  if (LJ_DUALNUM) {
    int32_t k = lj_num2int(n);
    if ((lua_Number)k == n) {
      setintV(&e1->u.nval, k);
      return 1;
    }
  }
  setnumV(&e1->u.nval, n);
  return 1;
}