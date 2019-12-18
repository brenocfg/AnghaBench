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
 int /*<<< orphan*/  CHECKPTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DT2ST (double,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VariantTimeToSystemTime ; 

__attribute__((used)) static void test_VariantTimeToSystemTime(void)
{
  CHECKPTR(VariantTimeToSystemTime);
  DT2ST(29221.0,1,1,1,1980,0,0,0,0);
  DT2ST(29222.0,1,2,1,1980,0,0,0,0);
}