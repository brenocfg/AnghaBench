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
 int /*<<< orphan*/  DATE ; 
 int /*<<< orphan*/  EXPECT (int) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  VarI2FromDate ; 

__attribute__((used)) static void test_VarI2FromDate(void)
{
  CONVVARS(DATE);

  CONVERT(VarI2FromDate, -32769.0); EXPECT_OVERFLOW;
  CONVERT(VarI2FromDate, -32768.0); EXPECT(-32768);
  CONVERT(VarI2FromDate, -1.0);   EXPECT(-1);
  CONVERT(VarI2FromDate, 0.0);    EXPECT(0);
  CONVERT(VarI2FromDate, 1.0);    EXPECT(1);
  CONVERT(VarI2FromDate, 32767.0);  EXPECT(32767);
  CONVERT(VarI2FromDate, 32768.0);  EXPECT_OVERFLOW;

  /* Rounding */
  CONVERT(VarI2FromDate, -1.5); EXPECT(-2);
  CONVERT(VarI2FromDate, -0.6); EXPECT(-1);
  CONVERT(VarI2FromDate, -0.5); EXPECT(0);
  CONVERT(VarI2FromDate, -0.4); EXPECT(0);
  CONVERT(VarI2FromDate, 0.4);  EXPECT(0);
  CONVERT(VarI2FromDate, 0.5);  EXPECT(0);
  CONVERT(VarI2FromDate, 0.6);  EXPECT(1);
  CONVERT(VarI2FromDate, 1.5);  EXPECT(2);
}