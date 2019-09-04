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
 int /*<<< orphan*/  EXPECT (int) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  VarI2FromR8 ; 

__attribute__((used)) static void test_VarI2FromR8(void)
{
  CONVVARS(DOUBLE);

  CONVERT(VarI2FromR8, -32769.0); EXPECT_OVERFLOW;
  CONVERT(VarI2FromR8, -32768.51); EXPECT_OVERFLOW;
  CONVERT(VarI2FromR8, -32768.5); EXPECT(-32768);
  CONVERT(VarI2FromR8, -32768.0); EXPECT(-32768);
  CONVERT(VarI2FromR8, -1.0);     EXPECT(-1);
  CONVERT(VarI2FromR8, 0.0);      EXPECT(0);
  CONVERT(VarI2FromR8, 1.0);      EXPECT(1);
  CONVERT(VarI2FromR8, 32767.0);  EXPECT(32767);
  CONVERT(VarI2FromR8, 32767.49);  EXPECT(32767);
  CONVERT(VarI2FromR8, 32767.5);  EXPECT_OVERFLOW;
  CONVERT(VarI2FromR8, 32768.0);  EXPECT_OVERFLOW;

  /* Rounding */
  CONVERT(VarI2FromR8, -1.5); EXPECT(-2);
  CONVERT(VarI2FromR8, -0.6); EXPECT(-1);
  CONVERT(VarI2FromR8, -0.5); EXPECT(0);
  CONVERT(VarI2FromR8, -0.4); EXPECT(0);
  CONVERT(VarI2FromR8, 0.4);  EXPECT(0);
  CONVERT(VarI2FromR8, 0.5);  EXPECT(0);
  CONVERT(VarI2FromR8, 0.6);  EXPECT(1);
  CONVERT(VarI2FromR8, 1.5);  EXPECT(2);
}