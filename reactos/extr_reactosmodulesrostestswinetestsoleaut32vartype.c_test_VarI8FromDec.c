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
 int /*<<< orphan*/  CONVERT_BADDEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONVERT_DEC (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECIMAL ; 
 int /*<<< orphan*/  EXPECTI8 (int) ; 
 int /*<<< orphan*/  VarI8FromDec ; 

__attribute__((used)) static void test_VarI8FromDec(void)
{
  CONVVARS(DECIMAL);

  CONVERT_BADDEC(VarI8FromDec);

  CONVERT_DEC(VarI8FromDec,0,0x80,0,128); EXPECTI8(-128);
  CONVERT_DEC(VarI8FromDec,0,0x80,0,1);   EXPECTI8(-1);
  CONVERT_DEC(VarI8FromDec,0,0,0,0);      EXPECTI8(0);
  CONVERT_DEC(VarI8FromDec,0,0,0,1);      EXPECTI8(1);
  CONVERT_DEC(VarI8FromDec,0,0,0,127);    EXPECTI8(127);

  CONVERT_DEC(VarI8FromDec,2,0x80,0,12700); EXPECTI8(-127);
  CONVERT_DEC(VarI8FromDec,2,0,0,12700);    EXPECTI8(127);
}