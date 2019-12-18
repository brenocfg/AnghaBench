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
 int /*<<< orphan*/  EXPECT (int) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  VarUI2FromDec ; 

__attribute__((used)) static void test_VarUI2FromDec(void)
{
  CONVVARS(DECIMAL);

  CONVERT_BADDEC(VarUI2FromDec);

  CONVERT_DEC(VarUI2FromDec,0,0x80,0,1);  EXPECT_OVERFLOW;
  CONVERT_DEC(VarUI2FromDec,0,0,0,0);     EXPECT(0);
  CONVERT_DEC(VarUI2FromDec,0,0,0,1);     EXPECT(1);
  CONVERT_DEC(VarUI2FromDec,0,0,0,65535); EXPECT(65535);
  CONVERT_DEC(VarUI2FromDec,0,0,0,65536); EXPECT_OVERFLOW;

  CONVERT_DEC(VarUI2FromDec,2,0x80,0,100);  EXPECT_OVERFLOW;
  CONVERT_DEC(VarUI2FromDec,2,0,0,6553500); EXPECT(65535);
  CONVERT_DEC(VarUI2FromDec,2,0,0,6553600); EXPECT_OVERFLOW;
}