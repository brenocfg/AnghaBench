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
 int /*<<< orphan*/  EXPECTCY (int) ; 
 int /*<<< orphan*/  MATHFIX (double) ; 
 int /*<<< orphan*/  MATHVARS1 ; 

__attribute__((used)) static void test_VarCyFix(void)
{
  MATHVARS1;

  MATHFIX(-1.0001); EXPECTCY(-1);
  MATHFIX(-1.4999); EXPECTCY(-1);
  MATHFIX(-1.5001); EXPECTCY(-1);
  MATHFIX(-1.9999); EXPECTCY(-1);
  MATHFIX(-0.0001); EXPECTCY(0);
  MATHFIX(-0.4999); EXPECTCY(0);
  MATHFIX(-0.5001); EXPECTCY(0);
  MATHFIX(-0.9999); EXPECTCY(0);
  MATHFIX(0.0001);  EXPECTCY(0);
  MATHFIX(0.4999);  EXPECTCY(0);
  MATHFIX(0.5001);  EXPECTCY(0);
  MATHFIX(0.9999);  EXPECTCY(0);
  MATHFIX(1.0001);  EXPECTCY(1);
  MATHFIX(1.4999);  EXPECTCY(1);
  MATHFIX(1.5001);  EXPECTCY(1);
  MATHFIX(1.9999);  EXPECTCY(1);
}