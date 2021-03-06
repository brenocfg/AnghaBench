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
 int /*<<< orphan*/  VarI4FromR8 ; 

__attribute__((used)) static void test_VarI4FromR8(void)
{
  CONVVARS(DOUBLE);

  CONVERT(VarI4FromR8, -2147483649.0); EXPECT_OVERFLOW;
  CONVERT(VarI4FromR8, -2147483648.51); EXPECT_OVERFLOW;
  CONVERT(VarI4FromR8, -2147483648.5); EXPECT(-2147483647 - 1);
  CONVERT(VarI4FromR8, -2147483648.0); EXPECT(-2147483647 - 1);
  CONVERT(VarI4FromR8, -1.0);          EXPECT(-1);
  CONVERT(VarI4FromR8, 0.0);           EXPECT(0);
  CONVERT(VarI4FromR8, 1.0);           EXPECT(1);
  CONVERT(VarI4FromR8, 2147483647.0);  EXPECT(2147483647);
  CONVERT(VarI4FromR8, 2147483647.49);  EXPECT(2147483647);
  CONVERT(VarI4FromR8, 2147483647.5);  EXPECT_OVERFLOW;
  CONVERT(VarI4FromR8, 2147483648.0);  EXPECT_OVERFLOW;

  CONVERT(VarI4FromR8, -1.5); EXPECT(-2);
  CONVERT(VarI4FromR8, -0.6); EXPECT(-1);
  CONVERT(VarI4FromR8, -0.5); EXPECT(0);
  CONVERT(VarI4FromR8, -0.4); EXPECT(0);
  CONVERT(VarI4FromR8, 0.4);  EXPECT(0);
  CONVERT(VarI4FromR8, 0.5);  EXPECT(0);
  CONVERT(VarI4FromR8, 0.6);  EXPECT(1);
  CONVERT(VarI4FromR8, 1.5);  EXPECT(2);
}