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
 int /*<<< orphan*/  EXPECT (int) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  VarI2FromCy ; 

__attribute__((used)) static void test_VarI2FromCy(void)
{
  CONVVARS(CY);

  CONVERT_CY(VarI2FromCy,-32769); EXPECT_OVERFLOW;
  CONVERT_CY(VarI2FromCy,-32768); EXPECT(32768);
  CONVERT_CY(VarI2FromCy,-1);     EXPECT(-1);
  CONVERT_CY(VarI2FromCy,0);      EXPECT(0);
  CONVERT_CY(VarI2FromCy,1);      EXPECT(1);
  CONVERT_CY(VarI2FromCy,32767);  EXPECT(32767);
  CONVERT_CY(VarI2FromCy,32768);  EXPECT_OVERFLOW;

  /* Rounding */
  CONVERT_CY(VarI2FromCy,-1.5); EXPECT(-2);
  CONVERT_CY(VarI2FromCy,-0.6); EXPECT(-1);
  CONVERT_CY(VarI2FromCy,-0.5); EXPECT(0);
  CONVERT_CY(VarI2FromCy,-0.4); EXPECT(0);
  CONVERT_CY(VarI2FromCy,0.4);  EXPECT(0);
  CONVERT_CY(VarI2FromCy,0.5);  EXPECT(0);
  CONVERT_CY(VarI2FromCy,0.6);  EXPECT(1);
  CONVERT_CY(VarI2FromCy,1.5);  EXPECT(2);
}