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
 int /*<<< orphan*/  LONG64 ; 
 int /*<<< orphan*/  VarI2FromI8 ; 

__attribute__((used)) static void test_VarI2FromI8(void)
{
  CONVVARS(LONG64);

  CONVERT(VarI2FromI8, -32769); EXPECT_OVERFLOW;
  CONVERT(VarI2FromI8, -32768); EXPECT(-32768);
  CONVERT(VarI2FromI8, 32767);  EXPECT(32767);
  CONVERT(VarI2FromI8, 32768);  EXPECT_OVERFLOW;
}