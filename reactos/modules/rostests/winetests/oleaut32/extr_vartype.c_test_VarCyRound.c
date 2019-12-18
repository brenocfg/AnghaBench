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
 int /*<<< orphan*/  EXPECTCY (int) ; 
 int /*<<< orphan*/  EXPECT_INVALID ; 
 int /*<<< orphan*/  MATHRND (double,int) ; 
 int /*<<< orphan*/  MATHVARS1 ; 

__attribute__((used)) static void test_VarCyRound(void)
{
  MATHVARS1;
  int right;

  MATHRND(0.5432, 5);  EXPECTCY(0.5432);
  MATHRND(0.5432, 4);  EXPECTCY(0.5432);
  MATHRND(0.5432, 3);  EXPECTCY(0.543);
  MATHRND(0.5432, 2);  EXPECTCY(0.54);
  MATHRND(0.5432, 1);  EXPECTCY(0.5);
  MATHRND(0.5532, 0);  EXPECTCY(1);
  MATHRND(0.5532, -1); EXPECT_INVALID;

  MATHRND(0.5568, 5);  EXPECTCY(0.5568);
  MATHRND(0.5568, 4);  EXPECTCY(0.5568);
  MATHRND(0.5568, 3);  EXPECTCY(0.557);
  MATHRND(0.5568, 2);  EXPECTCY(0.56);
  MATHRND(0.5568, 1);  EXPECTCY(0.6);
  MATHRND(0.5568, 0);  EXPECTCY(1);
  MATHRND(0.5568, -1); EXPECT_INVALID;

  MATHRND(0.4999, 0); EXPECTCY(0);
  MATHRND(0.5000, 0); EXPECTCY(0);
  MATHRND(0.5001, 0); EXPECTCY(1);
  MATHRND(1.4999, 0); EXPECTCY(1);
  MATHRND(1.5000, 0); EXPECTCY(2);
  MATHRND(1.5001, 0); EXPECTCY(2);
}