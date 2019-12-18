#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  jit_State ;
typedef  int int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  op2; int /*<<< orphan*/  o; } ;
typedef  int /*<<< orphan*/  TRef ;

/* Variables and functions */
 int /*<<< orphan*/  IR_BSHL ; 
 int /*<<< orphan*/  LEFTFOLD ; 
 int /*<<< orphan*/  NEXTFOLD ; 
 int /*<<< orphan*/  RETRYFOLD ; 
 int /*<<< orphan*/  RIGHTFOLD ; 
 TYPE_1__* fins ; 
 int /*<<< orphan*/  lj_fls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TRef simplify_intmul_k(jit_State *J, int32_t k)
{
  /* Note: many more simplifications are possible, e.g. 2^k1 +- 2^k2.
  ** But this is mainly intended for simple address arithmetic.
  ** Also it's easier for the backend to optimize the original multiplies.
  */
  if (k == 0) {  /* i * 0 ==> 0 */
    return RIGHTFOLD;
  } else if (k == 1) {  /* i * 1 ==> i */
    return LEFTFOLD;
  } else if ((k & (k-1)) == 0) {  /* i * 2^k ==> i << k */
    fins->o = IR_BSHL;
    fins->op2 = lj_ir_kint(J, lj_fls((uint32_t)k));
    return RETRYFOLD;
  }
  return NEXTFOLD;
}