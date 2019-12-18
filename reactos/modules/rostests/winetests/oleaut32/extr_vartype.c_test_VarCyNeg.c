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
 int /*<<< orphan*/  EXPECTCY64 (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  MATH1 (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  MATHVARS1 ; 
 int /*<<< orphan*/  VarCyNeg ; 

__attribute__((used)) static void test_VarCyNeg(void)
{
  MATHVARS1;

  MATH1(VarCyNeg, 0.5); EXPECTCY(-0.5);
  MATH1(VarCyNeg, -0.5); EXPECTCY(0.5);
  MATH1(VarCyNeg, 922337203685476.0);  EXPECTCY64(2147483648ul,15808);
  MATH1(VarCyNeg, -922337203685476.0); EXPECTCY64(2147483647ul,4294951488ul);
}