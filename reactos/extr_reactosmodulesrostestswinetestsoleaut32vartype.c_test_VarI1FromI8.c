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
 int /*<<< orphan*/  LONG64 ; 
 int /*<<< orphan*/  VarI1FromI8 ; 

__attribute__((used)) static void test_VarI1FromI8(void)
{
  CONVVARS(LONG64);
  int i;

  CONVERT(VarI1FromI8, -129);   EXPECT_OVERFLOW;
  CONVERTRANGE(VarI1FromI8, -127, 128);
  CONVERT(VarI1FromI8, 128);    EXPECT_OVERFLOW;
}