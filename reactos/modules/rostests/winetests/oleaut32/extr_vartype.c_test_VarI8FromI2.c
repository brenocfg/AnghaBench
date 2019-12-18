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
 int /*<<< orphan*/  EXPECTI8 (int) ; 
 int /*<<< orphan*/  SHORT ; 
 int /*<<< orphan*/  VarI8FromI2 ; 

__attribute__((used)) static void test_VarI8FromI2(void)
{
  CONVVARS(SHORT);
  int i;

  for (i = -32768; i < 32768; i++)
  {
    CONVERT(VarI8FromI2,i); EXPECTI8(i);
  }
}