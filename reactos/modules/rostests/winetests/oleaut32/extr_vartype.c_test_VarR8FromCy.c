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
 int /*<<< orphan*/  EXPECT (double) ; 
 int /*<<< orphan*/  VarR8FromCy ; 

__attribute__((used)) static void test_VarR8FromCy(void)
{
  CONVVARS(CY);

  CONVERT_CY(VarR8FromCy,-32769); EXPECT(-32769.0);
  CONVERT_CY(VarR8FromCy,-32768); EXPECT(-32768.0);
  CONVERT_CY(VarR8FromCy,-1);     EXPECT(-1.0);
  CONVERT_CY(VarR8FromCy,0);      EXPECT(0.0);
  CONVERT_CY(VarR8FromCy,1);      EXPECT(1.0);
  CONVERT_CY(VarR8FromCy,32767);  EXPECT(32767.0);
  CONVERT_CY(VarR8FromCy,32768);  EXPECT(32768.0);

  CONVERT_CY(VarR8FromCy,-1.5); EXPECT(-1.5);
  CONVERT_CY(VarR8FromCy,-0.6); EXPECT(-0.6);
  CONVERT_CY(VarR8FromCy,-0.5); EXPECT(-0.5);
  CONVERT_CY(VarR8FromCy,-0.4); EXPECT(-0.4);
  CONVERT_CY(VarR8FromCy,0.4);  EXPECT(0.4);
  CONVERT_CY(VarR8FromCy,0.5);  EXPECT(0.5);
  CONVERT_CY(VarR8FromCy,0.6);  EXPECT(0.6);
  CONVERT_CY(VarR8FromCy,1.5);  EXPECT(1.5);
}