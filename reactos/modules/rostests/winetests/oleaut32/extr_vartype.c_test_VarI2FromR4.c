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
 int /*<<< orphan*/  VarI2FromR4 ; 

__attribute__((used)) static void test_VarI2FromR4(void)
{
  CONVVARS(FLOAT);

  CONVERT(VarI2FromR4, -32769.0f); EXPECT_OVERFLOW;
  CONVERT(VarI2FromR4, -32768.51f); EXPECT_OVERFLOW;
  CONVERT(VarI2FromR4, -32768.5f); EXPECT(-32768);
  CONVERT(VarI2FromR4, -32768.0f); EXPECT(-32768);
  CONVERT(VarI2FromR4, -1.0f);     EXPECT(-1);
  CONVERT(VarI2FromR4, 0.0f);      EXPECT(0);
  CONVERT(VarI2FromR4, 1.0f);      EXPECT(1);
  CONVERT(VarI2FromR4, 32767.0f);  EXPECT(32767);
  CONVERT(VarI2FromR4, 32767.49f);  EXPECT(32767);
  CONVERT(VarI2FromR4, 32767.5f);  EXPECT_OVERFLOW;
  CONVERT(VarI2FromR4, 32768.0f);  EXPECT_OVERFLOW;

  /* Rounding */
  CONVERT(VarI2FromR4, -1.5f); EXPECT(-2);
  CONVERT(VarI2FromR4, -0.6f); EXPECT(-1);
  CONVERT(VarI2FromR4, -0.5f); EXPECT(0);
  CONVERT(VarI2FromR4, -0.4f); EXPECT(0);
  CONVERT(VarI2FromR4, 0.4f);  EXPECT(0);
  CONVERT(VarI2FromR4, 0.5f);  EXPECT(0);
  CONVERT(VarI2FromR4, 0.6f);  EXPECT(1);
  CONVERT(VarI2FromR4, 1.5f);  EXPECT(2);
}