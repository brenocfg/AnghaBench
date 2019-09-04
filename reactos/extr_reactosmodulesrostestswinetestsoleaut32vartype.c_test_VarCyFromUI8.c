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
 int /*<<< orphan*/  CONVERT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CONVERT_I8 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPECTCY (int) ; 
 int /*<<< orphan*/  EXPECTCY64 (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  ULONG64 ; 
 int /*<<< orphan*/  VarCyFromUI8 ; 

__attribute__((used)) static void test_VarCyFromUI8(void)
{
  CONVVARS(ULONG64);

  CONVERT(VarCyFromUI8, 0); EXPECTCY(0);
  CONVERT(VarCyFromUI8, 1); EXPECTCY(1);
  CONVERT_I8(VarCyFromUI8, 214748, 1566804068); EXPECTCY64(2147483647ul, 4294951488ul);
  CONVERT_I8(VarCyFromUI8, 214748, 1566804069); EXPECTCY64(2147483647ul, 4294961488ul);
  CONVERT_I8(VarCyFromUI8, 214748, 1566804070); EXPECT_OVERFLOW;
  CONVERT_I8(VarCyFromUI8, 214749, 1566804068); EXPECT_OVERFLOW;
}