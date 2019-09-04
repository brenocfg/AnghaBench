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
 int /*<<< orphan*/  EXPECT (double) ; 
 int /*<<< orphan*/  VarDateFromDec ; 

__attribute__((used)) static void test_VarDateFromDec(void)
{
  CONVVARS(DECIMAL);

  CONVERT_BADDEC(VarDateFromDec);

  CONVERT_DEC(VarDateFromDec,0,0x80,0,32768); EXPECT(-32768.0);
  CONVERT_DEC(VarDateFromDec,0,0x80,0,1);     EXPECT(-1.0);
  CONVERT_DEC(VarDateFromDec,0,0,0,0);        EXPECT(0.0);
  CONVERT_DEC(VarDateFromDec,0,0,0,1);        EXPECT(1.0);
  CONVERT_DEC(VarDateFromDec,0,0,0,32767);    EXPECT(32767.0);

  CONVERT_DEC(VarDateFromDec,2,0x80,0,3276800); EXPECT(-32768.0);
  CONVERT_DEC(VarDateFromDec,2,0,0,3276700);    EXPECT(32767.0);
}