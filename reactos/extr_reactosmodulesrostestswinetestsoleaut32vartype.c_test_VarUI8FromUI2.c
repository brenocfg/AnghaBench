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
 int /*<<< orphan*/  USHORT ; 
 int /*<<< orphan*/  VarUI8FromUI2 ; 

__attribute__((used)) static void test_VarUI8FromUI2(void)
{
  CONVVARS(USHORT);
  int i;

  for (i = 0; i < 65535; i++)
  {
    CONVERT(VarUI8FromUI2,i); EXPECTI8(i);
  }
}