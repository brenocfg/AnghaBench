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
 int /*<<< orphan*/  CONVERT_I8 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPECTI8 (int) ; 
 int /*<<< orphan*/  EXPECTI864 (int,int) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  ULONG64 ; 
 int /*<<< orphan*/  VarI8FromUI8 ; 

__attribute__((used)) static void test_VarI8FromUI8(void)
{
  CONVVARS(ULONG64);

  CONVERT(VarI8FromUI8, 0); EXPECTI8(0);
  CONVERT(VarI8FromUI8, 1); EXPECTI8(1);
  CONVERT_I8(VarI8FromUI8, 0x7fffffff, 0xffffffff); EXPECTI864(0x7fffffff, 0xffffffff);
  CONVERT_I8(VarI8FromUI8, 0x80000000, 0);          EXPECT_OVERFLOW;
}