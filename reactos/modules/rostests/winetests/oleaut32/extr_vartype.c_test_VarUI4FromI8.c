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
 int /*<<< orphan*/  CONVERT (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  CONVERT_I8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPECT (unsigned long) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  LONG64 ; 
 int /*<<< orphan*/  VarUI4FromI8 ; 

__attribute__((used)) static void test_VarUI4FromI8(void)
{
  CONVVARS(LONG64);

  CONVERT(VarUI4FromI8, -1);           EXPECT_OVERFLOW;
  CONVERT(VarUI4FromI8, 0);            EXPECT(0);
  CONVERT(VarUI4FromI8, 1);            EXPECT(1);
  CONVERT(VarUI4FromI8, 4294967295ul); EXPECT(4294967295ul);
  CONVERT_I8(VarUI4FromI8, 1, 0);      EXPECT_OVERFLOW;
}