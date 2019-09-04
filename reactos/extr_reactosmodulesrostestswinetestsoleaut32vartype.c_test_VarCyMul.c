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

/* Variables and functions */
 int /*<<< orphan*/  EXPECTCY (double) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  MATH2 (int /*<<< orphan*/ ,double,int) ; 
 int /*<<< orphan*/  MATHVARS2 ; 
 int /*<<< orphan*/  VarCyMul ; 

__attribute__((used)) static void test_VarCyMul(void)
{
  MATHVARS2;

  MATH2(VarCyMul, 534443.0, 0.0); EXPECTCY(0);
  MATH2(VarCyMul, 0.5, 0.5);      EXPECTCY(0.25);
  MATH2(VarCyMul, 0.5, -0.4);     EXPECTCY(-0.2);
  MATH2(VarCyMul, 0.5, -0.6);     EXPECTCY(-0.3);
  MATH2(VarCyMul, -0.5, -0.5);    EXPECTCY(0.25);
  MATH2(VarCyMul, 922337203685476.0, 20000); EXPECT_OVERFLOW;
}