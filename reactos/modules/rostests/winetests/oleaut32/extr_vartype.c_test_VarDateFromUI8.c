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
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int DATE_MAX ; 
 int /*<<< orphan*/  EXPECT (int) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  ULONG64 ; 
 int /*<<< orphan*/  VarDateFromUI8 ; 

__attribute__((used)) static void test_VarDateFromUI8(void)
{
  CONVVARS(ULONG64);

  CONVERT(VarDateFromUI8, 0);          EXPECT(0.0);
  CONVERT(VarDateFromUI8, 1);          EXPECT(1.0);
  CONVERT(VarDateFromUI8, DATE_MAX);   EXPECT(DATE_MAX);
  CONVERT(VarDateFromUI8, DATE_MAX+1); EXPECT_OVERFLOW;
}