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
 int /*<<< orphan*/  EXPECT (int) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  FLOAT ; 
 int /*<<< orphan*/  VarUI1FromR4 ; 

__attribute__((used)) static void test_VarUI1FromR4(void)
{
  CONVVARS(FLOAT);

  CONVERT(VarUI1FromR4, -1.0f);  EXPECT_OVERFLOW;
  CONVERT(VarUI1FromR4, -0.51f);  EXPECT_OVERFLOW;
  CONVERT(VarUI1FromR4, -0.5f);   EXPECT(0);
  CONVERT(VarUI1FromR4, 0.0f);   EXPECT(0);
  CONVERT(VarUI1FromR4, 1.0f);   EXPECT(1);
  CONVERT(VarUI1FromR4, 255.0f); EXPECT(255);
  CONVERT(VarUI1FromR4, 255.49f); EXPECT(255);
  CONVERT(VarUI1FromR4, 255.5f); EXPECT_OVERFLOW;
  CONVERT(VarUI1FromR4, 256.0f); EXPECT_OVERFLOW;

  /* Rounding */
  CONVERT(VarUI1FromR4, -1.5f); EXPECT_OVERFLOW;
  CONVERT(VarUI1FromR4, -0.6f); EXPECT_OVERFLOW;
  CONVERT(VarUI1FromR4, -0.5f); EXPECT(0);
  CONVERT(VarUI1FromR4, -0.4f); EXPECT(0);
  CONVERT(VarUI1FromR4, 0.4f);  EXPECT(0);
  CONVERT(VarUI1FromR4, 0.5f);  EXPECT(0);
  CONVERT(VarUI1FromR4, 0.6f);  EXPECT(1);
  CONVERT(VarUI1FromR4, 1.5f);  EXPECT(2);
}