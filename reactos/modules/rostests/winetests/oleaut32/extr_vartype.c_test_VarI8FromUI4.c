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
 int /*<<< orphan*/  EXPECTI8 (unsigned long) ; 
 int /*<<< orphan*/  ULONG ; 
 int /*<<< orphan*/  VarI8FromUI4 ; 

__attribute__((used)) static void test_VarI8FromUI4(void)
{
  CONVVARS(ULONG);

  CONVERT(VarI8FromUI4, 0);            EXPECTI8(0);
  CONVERT(VarI8FromUI4, 1);            EXPECTI8(1);
  CONVERT(VarI8FromUI4, 4294967295ul); EXPECTI8(4294967295ul);
}