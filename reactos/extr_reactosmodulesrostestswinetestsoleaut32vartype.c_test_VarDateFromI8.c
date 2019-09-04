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
 int DATE_MIN ; 
 int /*<<< orphan*/  EXPECT (int) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  LONG64 ; 
 int /*<<< orphan*/  VarDateFromI8 ; 

__attribute__((used)) static void test_VarDateFromI8(void)
{
  CONVVARS(LONG64);

  CONVERT(VarDateFromI8, DATE_MIN-1); EXPECT_OVERFLOW;
  CONVERT(VarDateFromI8, DATE_MIN);   EXPECT(DATE_MIN);
  CONVERT(VarDateFromI8, -1);         EXPECT(-1.0);
  CONVERT(VarDateFromI8, 0);          EXPECT(0.0);
  CONVERT(VarDateFromI8, 1);          EXPECT(1.0);
  CONVERT(VarDateFromI8, DATE_MAX);   EXPECT(DATE_MAX);
  CONVERT(VarDateFromI8, DATE_MAX+1); EXPECT_OVERFLOW;
}