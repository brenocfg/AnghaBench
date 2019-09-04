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
 int /*<<< orphan*/  CONVERT_CY (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CY ; 
 int /*<<< orphan*/  EXPECTI8 (int) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  VarUI8FromCy ; 

__attribute__((used)) static void test_VarUI8FromCy(void)
{
  CONVVARS(CY);

  CONVERT_CY(VarUI8FromCy,-1);  EXPECT_OVERFLOW;
  CONVERT_CY(VarUI8FromCy,0);   EXPECTI8(0);
  CONVERT_CY(VarUI8FromCy,1);   EXPECTI8(1);
  CONVERT_CY(VarUI8FromCy,255); EXPECTI8(255);

  CONVERT_CY(VarUI8FromCy,-1.5); EXPECT_OVERFLOW;
  CONVERT_CY(VarUI8FromCy,-0.6); EXPECT_OVERFLOW;
  CONVERT_CY(VarUI8FromCy,-0.5); EXPECTI8(0);
  CONVERT_CY(VarUI8FromCy,-0.4); EXPECTI8(0);
  CONVERT_CY(VarUI8FromCy,0.4);  EXPECTI8(0);
  CONVERT_CY(VarUI8FromCy,0.5);  EXPECTI8(0);
  CONVERT_CY(VarUI8FromCy,0.6);  EXPECTI8(1);
  CONVERT_CY(VarUI8FromCy,1.5);  EXPECTI8(2);
}