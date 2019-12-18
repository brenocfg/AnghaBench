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
 int /*<<< orphan*/  EXPECTDEC (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VarDecFromCy ; 

__attribute__((used)) static void test_VarDecFromCy(void)
{
  CONVVARS(CY);

  CONVERT_CY(VarDecFromCy, -1);  EXPECTDEC(4,0x80,0,10000);
  CONVERT_CY(VarDecFromCy, 0);   EXPECTDEC(4,0,0,0);
  CONVERT_CY(VarDecFromCy, 1);   EXPECTDEC(4,0,0,10000);
  CONVERT_CY(VarDecFromCy, 0.5); EXPECTDEC(4,0,0,5000);
}