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
 int /*<<< orphan*/  CONVERT_DEC64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECIMAL ; 
 int /*<<< orphan*/  EXPECTCY (int) ; 
 int /*<<< orphan*/  EXPECTCY64 (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  VarCyFromDec ; 

__attribute__((used)) static void test_VarCyFromDec(void)
{
  CONVVARS(DECIMAL);

  CONVERT_BADDEC(VarCyFromDec);

  CONVERT_DEC(VarCyFromDec,0,0x80,0,1); EXPECTCY(-1);
  CONVERT_DEC(VarCyFromDec,0,0,0,0);    EXPECTCY(0);
  CONVERT_DEC(VarCyFromDec,0,0,0,1);    EXPECTCY(1);

  CONVERT_DEC64(VarCyFromDec,0,0,0,214748, 1566804068); EXPECTCY64(2147483647ul, 4294951488ul);
  CONVERT_DEC64(VarCyFromDec,0,0,0,214748, 1566804069); EXPECTCY64(2147483647ul, 4294961488ul);
  CONVERT_DEC64(VarCyFromDec,0,0,0,214748, 1566804070); EXPECT_OVERFLOW;
  CONVERT_DEC64(VarCyFromDec,0,0,0,214749, 1566804068); EXPECT_OVERFLOW;

  CONVERT_DEC(VarCyFromDec,2,0,0,100);     EXPECTCY(1);
  CONVERT_DEC(VarCyFromDec,2,0x80,0,100);  EXPECTCY(-1);
  CONVERT_DEC(VarCyFromDec,2,0x80,0,1);    EXPECTCY(-0.01);
  CONVERT_DEC(VarCyFromDec,2,0,0,1);       EXPECTCY(0.01);
  CONVERT_DEC(VarCyFromDec,2,0x80,0,1);    EXPECTCY(-0.01);
  CONVERT_DEC(VarCyFromDec,2,0,0,999);     EXPECTCY(9.99);
  CONVERT_DEC(VarCyFromDec,2,0x80,0,999);  EXPECTCY(-9.99);
  CONVERT_DEC(VarCyFromDec,2,0,0,1500);    EXPECTCY(15);
  CONVERT_DEC(VarCyFromDec,2,0x80,0,1500); EXPECTCY(-15);
}