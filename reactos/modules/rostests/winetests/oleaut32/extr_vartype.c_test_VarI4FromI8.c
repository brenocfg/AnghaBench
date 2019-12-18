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
 int /*<<< orphan*/  CONVERT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CONVERT_I8 (int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPECT (int) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  LONG64 ; 
 int /*<<< orphan*/  VarI4FromI8 ; 

__attribute__((used)) static void test_VarI4FromI8(void)
{
  CONVVARS(LONG64);

  CONVERT(VarI4FromI8, -1);                   EXPECT(-1);
  CONVERT(VarI4FromI8, 0);                    EXPECT(0);
  CONVERT(VarI4FromI8, 1);                    EXPECT(1);

  CONVERT_I8(VarI4FromI8, -1, 2147483647ul); EXPECT_OVERFLOW;
  CONVERT_I8(VarI4FromI8, -1, 2147483648ul); EXPECT(-2147483647 - 1);
  CONVERT_I8(VarI4FromI8, 0, 2147483647ul);  EXPECT(2147483647);
  CONVERT_I8(VarI4FromI8, 0, 2147483648ul);  EXPECT_OVERFLOW;
}