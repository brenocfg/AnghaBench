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
 int /*<<< orphan*/  CONVERTRANGE (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  LONG ; 
 int /*<<< orphan*/  VarI2FromI4 ; 

__attribute__((used)) static void test_VarI2FromI4(void)
{
  CONVVARS(LONG);
  int i;

  CONVERT(VarI2FromI4, -32769); EXPECT_OVERFLOW;
  CONVERTRANGE(VarI2FromI4, -32768, 32768);
  CONVERT(VarI2FromI4, 32768);  EXPECT_OVERFLOW;
}