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
 int /*<<< orphan*/  CONVERT (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPECTI8 (int) ; 
 int /*<<< orphan*/  FLOAT ; 
 int /*<<< orphan*/  VarI8FromR4 ; 

__attribute__((used)) static void test_VarI8FromR4(void)
{
  CONVVARS(FLOAT);

  CONVERT(VarI8FromR4, -128.0f); EXPECTI8(-128);
  CONVERT(VarI8FromR4, -1.0f);   EXPECTI8(-1);
  CONVERT(VarI8FromR4, 0.0f);    EXPECTI8(0);
  CONVERT(VarI8FromR4, 1.0f);    EXPECTI8(1);
  CONVERT(VarI8FromR4, 127.0f);  EXPECTI8(127);

  CONVERT(VarI8FromR4, -1.5f); EXPECTI8(-2);
  CONVERT(VarI8FromR4, -0.6f); EXPECTI8(-1);
  CONVERT(VarI8FromR4, -0.5f); EXPECTI8(0);
  CONVERT(VarI8FromR4, -0.4f); EXPECTI8(0);
  CONVERT(VarI8FromR4, 0.4f);  EXPECTI8(0);
  CONVERT(VarI8FromR4, 0.5f);  EXPECTI8(0);
  CONVERT(VarI8FromR4, 0.6f);  EXPECTI8(1);
  CONVERT(VarI8FromR4, 1.5f);  EXPECTI8(2);
}