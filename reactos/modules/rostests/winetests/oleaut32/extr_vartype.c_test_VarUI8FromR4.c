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
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  FLOAT ; 
 int /*<<< orphan*/  VarUI8FromR4 ; 

__attribute__((used)) static void test_VarUI8FromR4(void)
{
  CONVVARS(FLOAT);

  CONVERT(VarUI8FromR4, -1.0f);  EXPECT_OVERFLOW;
  CONVERT(VarUI8FromR4, 0.0f);   EXPECTI8(0);
  CONVERT(VarUI8FromR4, 1.0f);   EXPECTI8(1);
  CONVERT(VarUI8FromR4, 255.0f); EXPECTI8(255);

  CONVERT(VarUI8FromR4, -1.5f); EXPECT_OVERFLOW;
  CONVERT(VarUI8FromR4, -0.6f); EXPECT_OVERFLOW;
  CONVERT(VarUI8FromR4, -0.5f); EXPECTI8(0);
  CONVERT(VarUI8FromR4, -0.4f); EXPECTI8(0);
  CONVERT(VarUI8FromR4, 0.4f);  EXPECTI8(0);
  CONVERT(VarUI8FromR4, 0.5f);  EXPECTI8(0);
  CONVERT(VarUI8FromR4, 0.6f);  EXPECTI8(1);
  CONVERT(VarUI8FromR4, 1.5f);  EXPECTI8(2);
}