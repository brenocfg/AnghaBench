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
 int /*<<< orphan*/  CONVERT (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DOUBLE ; 
 int /*<<< orphan*/  EXPECTI8 (int) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  VarUI8FromR8 ; 

__attribute__((used)) static void test_VarUI8FromR8(void)
{
  CONVVARS(DOUBLE);

  CONVERT(VarUI8FromR8, -1.0);  EXPECT_OVERFLOW;
  CONVERT(VarUI8FromR8, 0.0);   EXPECTI8(0);
  CONVERT(VarUI8FromR8, 1.0);   EXPECTI8(1);
  CONVERT(VarUI8FromR8, 255.0); EXPECTI8(255);

  CONVERT(VarUI8FromR8, -1.5); EXPECT_OVERFLOW;
  CONVERT(VarUI8FromR8, -0.6); EXPECT_OVERFLOW;
  CONVERT(VarUI8FromR8, -0.5); EXPECTI8(0);
  CONVERT(VarUI8FromR8, -0.4); EXPECTI8(0);
  CONVERT(VarUI8FromR8, 0.4);  EXPECTI8(0);
  CONVERT(VarUI8FromR8, 0.5);  EXPECTI8(0);
  CONVERT(VarUI8FromR8, 0.6);  EXPECTI8(1);
  CONVERT(VarUI8FromR8, 1.5);  EXPECTI8(2);
}