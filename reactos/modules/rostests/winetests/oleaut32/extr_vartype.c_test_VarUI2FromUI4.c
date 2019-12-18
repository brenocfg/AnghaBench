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
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPECT (int) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  ULONG ; 
 int /*<<< orphan*/  VarUI2FromUI4 ; 

__attribute__((used)) static void test_VarUI2FromUI4(void)
{
  CONVVARS(ULONG);

  CONVERT(VarUI2FromUI4, 0);     EXPECT(0);
  CONVERT(VarUI2FromUI4, 65535); EXPECT(65535);
  CONVERT(VarUI2FromUI4, 65536); EXPECT_OVERFLOW;
}