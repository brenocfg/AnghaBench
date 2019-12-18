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
 int /*<<< orphan*/  VarI4FromDate ; 

__attribute__((used)) static void test_VarI4FromDate(void)
{
  CONVVARS(DATE);

  CONVERT(VarI4FromDate, -2147483649.0); EXPECT_OVERFLOW;
  CONVERT(VarI4FromDate, -2147483648.0); EXPECT(-2147483647 - 1);
  CONVERT(VarI4FromDate, -1.0);          EXPECT(-1);
  CONVERT(VarI4FromDate, 0.0);           EXPECT(0);
  CONVERT(VarI4FromDate, 1.0);           EXPECT(1);
  CONVERT(VarI4FromDate, 2147483647.0);  EXPECT(2147483647);
  CONVERT(VarI4FromDate, 2147483648.0);  EXPECT_OVERFLOW;

  CONVERT(VarI4FromDate, -1.5); EXPECT(-2);
  CONVERT(VarI4FromDate, -0.6); EXPECT(-1);
  CONVERT(VarI4FromDate, -0.5); EXPECT(0);
  CONVERT(VarI4FromDate, -0.4); EXPECT(0);
  CONVERT(VarI4FromDate, 0.4);  EXPECT(0);
  CONVERT(VarI4FromDate, 0.5);  EXPECT(0);
  CONVERT(VarI4FromDate, 0.6);  EXPECT(1);
  CONVERT(VarI4FromDate, 1.5);  EXPECT(2);
}