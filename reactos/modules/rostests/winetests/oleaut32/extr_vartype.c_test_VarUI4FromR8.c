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
 int /*<<< orphan*/  VarUI4FromR4 ; 
 int /*<<< orphan*/  VarUI4FromR8 ; 

__attribute__((used)) static void test_VarUI4FromR8(void)
{
  CONVVARS(DOUBLE);

  CONVERT(VarUI4FromR8, -1.0);         EXPECT_OVERFLOW;
  CONVERT(VarUI4FromR4, -0.51f);       EXPECT_OVERFLOW;
  CONVERT(VarUI4FromR4, -0.5f);        EXPECT(0);
  CONVERT(VarUI4FromR8, 0.0);          EXPECT(0);
  CONVERT(VarUI4FromR8, 1.0);          EXPECT(1);
  CONVERT(VarUI4FromR8, 4294967295.0); EXPECT(4294967295ul);
  CONVERT(VarUI4FromR8, 4294967295.49); EXPECT(4294967295ul);
  CONVERT(VarUI4FromR8, 4294967295.5); EXPECT_OVERFLOW;
  CONVERT(VarUI4FromR8, 4294967296.0); EXPECT_OVERFLOW;

  CONVERT(VarUI4FromR8, -1.5); EXPECT_OVERFLOW;
  CONVERT(VarUI4FromR8, -0.6); EXPECT_OVERFLOW;
  CONVERT(VarUI4FromR8, -0.5); EXPECT(0);
  CONVERT(VarUI4FromR8, -0.4); EXPECT(0);
  CONVERT(VarUI4FromR8, 0.4);  EXPECT(0);
  CONVERT(VarUI4FromR8, 0.5);  EXPECT(0);
  CONVERT(VarUI4FromR8, 0.6);  EXPECT(1);
  CONVERT(VarUI4FromR8, 1.5);  EXPECT(2);
}