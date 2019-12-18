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
 int /*<<< orphan*/  VarI8FromCy ; 

__attribute__((used)) static void test_VarI8FromCy(void)
{
  CONVVARS(CY);

  CONVERT_CY(VarI8FromCy,-128); EXPECTI8(-129);
  CONVERT_CY(VarI8FromCy,-1);   EXPECTI8(-2);
  CONVERT_CY(VarI8FromCy,0);    EXPECTI8(0);
  CONVERT_CY(VarI8FromCy,1);    EXPECTI8(1);
  CONVERT_CY(VarI8FromCy,127);  EXPECTI8(127);

  CONVERT_CY(VarI8FromCy,-1.5); EXPECTI8(-2);
  CONVERT_CY(VarI8FromCy,-0.6); EXPECTI8(-1);
  CONVERT_CY(VarI8FromCy,-0.5); EXPECTI8(-1);
  CONVERT_CY(VarI8FromCy,-0.4); EXPECTI8(-1);
  CONVERT_CY(VarI8FromCy,0.4);  EXPECTI8(0);
  CONVERT_CY(VarI8FromCy,0.5);  EXPECTI8(0);
  CONVERT_CY(VarI8FromCy,0.6);  EXPECTI8(1);
  CONVERT_CY(VarI8FromCy,1.5);  EXPECTI8(2);
}