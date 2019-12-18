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
 int /*<<< orphan*/  EXPECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ULONG64 ; 
 int /*<<< orphan*/  VARIANT_FALSE ; 
 int /*<<< orphan*/  VARIANT_TRUE ; 
 int /*<<< orphan*/  VarBoolFromUI8 ; 

__attribute__((used)) static void test_VarBoolFromUI8(void)
{
  CONVVARS(ULONG64);

  CONVERT(VarBoolFromUI8, 0); EXPECT(VARIANT_FALSE);
  CONVERT(VarBoolFromUI8, 1); EXPECT(VARIANT_TRUE);
}