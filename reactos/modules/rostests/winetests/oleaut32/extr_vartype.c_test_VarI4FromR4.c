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
 int /*<<< orphan*/  FLOAT ; 
 int /*<<< orphan*/  VarI4FromR4 ; 

__attribute__((used)) static void test_VarI4FromR4(void)
{
  CONVVARS(FLOAT);

  /* min/max values are not exactly representable in a float */
  CONVERT(VarI4FromR4, -1.0f); EXPECT(-1);
  CONVERT(VarI4FromR4, 0.0f);  EXPECT(0);
  CONVERT(VarI4FromR4, 1.0f);  EXPECT(1);

  CONVERT(VarI4FromR4, -1.5f); EXPECT(-2);
  CONVERT(VarI4FromR4, -0.6f); EXPECT(-1);
  CONVERT(VarI4FromR4, -0.5f); EXPECT(0);
  CONVERT(VarI4FromR4, -0.4f); EXPECT(0);
  CONVERT(VarI4FromR4, 0.4f);  EXPECT(0);
  CONVERT(VarI4FromR4, 0.5f);  EXPECT(0);
  CONVERT(VarI4FromR4, 0.6f);  EXPECT(1);
  CONVERT(VarI4FromR4, 1.5f);  EXPECT(2);
}