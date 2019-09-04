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
 int /*<<< orphan*/  CONVERT_DEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CONVERT_DEC64 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECIMAL ; 
 int /*<<< orphan*/  EXPECT (unsigned long) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  VarUI4FromDec ; 

__attribute__((used)) static void test_VarUI4FromDec(void)
{
  CONVVARS(DECIMAL);

  CONVERT_BADDEC(VarUI4FromDec);

  CONVERT_DEC(VarUI4FromDec,0,0x80,0,1);              EXPECT_OVERFLOW;
  CONVERT_DEC(VarUI4FromDec,0,0,0,0);                 EXPECT(0);
  CONVERT_DEC(VarUI4FromDec,0,0,0,1);                 EXPECT(1);
  CONVERT_DEC64(VarUI4FromDec,0,0,0,0,4294967295ul);  EXPECT(4294967295ul);
  CONVERT_DEC64(VarUI4FromDec,0,0,0,1,0);             EXPECT_OVERFLOW;

  CONVERT_DEC64(VarUI4FromDec,2,0,0,99,4294967196ul); EXPECT(4294967295ul);
  CONVERT_DEC64(VarUI4FromDec,2,0,0,100,0);           EXPECT_OVERFLOW;
}