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
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPECT (int) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  ULONG ; 
 int /*<<< orphan*/  VarI4FromUI4 ; 

__attribute__((used)) static void test_VarI4FromUI4(void)
{
  CONVVARS(ULONG);

  CONVERT(VarI4FromUI4, 0);            EXPECT(0);
  CONVERT(VarI4FromUI4, 1);            EXPECT(1);
  CONVERT(VarI4FromUI4, 2147483647);   EXPECT(2147483647);
  CONVERT(VarI4FromUI4, 2147483648ul); EXPECT_OVERFLOW;
}