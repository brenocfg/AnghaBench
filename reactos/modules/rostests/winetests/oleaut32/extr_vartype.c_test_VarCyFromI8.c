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
 int /*<<< orphan*/  LONG64 ; 
 int /*<<< orphan*/  VarCyFromI8 ; 

__attribute__((used)) static void test_VarCyFromI8(void)
{
  CONVVARS(LONG64);

  CONVERT_I8(VarCyFromI8, -214749, 2728163227ul);   EXPECT_OVERFLOW;
  CONVERT_I8(VarCyFromI8, -214749, 2728163228ul);   EXPECTCY64(2147483648ul,15808);
  CONVERT(VarCyFromI8, -1); EXPECTCY(-1);
  CONVERT(VarCyFromI8, 0);  EXPECTCY(0);
  CONVERT(VarCyFromI8, 1);  EXPECTCY(1);
  CONVERT_I8(VarCyFromI8, 214748, 1566804068); EXPECTCY64(2147483647ul, 4294951488ul);
  CONVERT_I8(VarCyFromI8, 214748, 1566804069); EXPECT_OVERFLOW;
}