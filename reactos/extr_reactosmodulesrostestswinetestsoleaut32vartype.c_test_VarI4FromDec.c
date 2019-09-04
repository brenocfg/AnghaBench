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
 int /*<<< orphan*/  CONVERT_DEC64 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECIMAL ; 
 int /*<<< orphan*/  EXPECT (int) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  VarI4FromDec ; 

__attribute__((used)) static void test_VarI4FromDec(void)
{
  CONVVARS(DECIMAL);

  CONVERT_BADDEC(VarI4FromDec);

  CONVERT_DEC(VarI4FromDec,0,0x80,0,1); EXPECT(-1);
  CONVERT_DEC(VarI4FromDec,0,0,0,0);    EXPECT(0);
  CONVERT_DEC(VarI4FromDec,0,0,0,1);    EXPECT(1);

  CONVERT_DEC64(VarI4FromDec,0,0x80,0,0,2147483649ul);  EXPECT_OVERFLOW;
  CONVERT_DEC64(VarI4FromDec,0,0x80,0,0,2147483648ul);  EXPECT(-2147483647 - 1);
  CONVERT_DEC64(VarI4FromDec,0,0,0,0,2147483647ul);     EXPECT(2147483647ul);
  CONVERT_DEC64(VarI4FromDec,0,0,0,0,2147483648ul);     EXPECT_OVERFLOW;

  CONVERT_DEC64(VarI4FromDec,2,0x80,0,50,100);       EXPECT_OVERFLOW;
  CONVERT_DEC64(VarI4FromDec,2,0x80,0,50,0);         EXPECT(-2147483647 - 1);
  CONVERT_DEC64(VarI4FromDec,2,0,0,49,4294967196ul); EXPECT(2147483647);
  CONVERT_DEC64(VarI4FromDec,2,0,0,50,0);            EXPECT_OVERFLOW;
}