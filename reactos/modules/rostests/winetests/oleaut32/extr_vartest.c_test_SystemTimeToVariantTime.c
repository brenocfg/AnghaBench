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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ST2DT (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  SystemTimeToVariantTime ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void test_SystemTimeToVariantTime(void)
{
  CHECKPTR(SystemTimeToVariantTime);
  ST2DT(1,1,1980,0,0,0,0,TRUE,29221.0);
  ST2DT(2,1,1980,0,0,0,0,TRUE,29222.0);
  ST2DT(0,1,1980,0,0,0,0,TRUE,29220.0);   /* Rolls back to 31 Dec 1899 */
  ST2DT(1,13,1980,0,0,0,0,FALSE,29587.0); /* Fails on invalid month */
  ST2DT(32,1,1980,0,0,0,0,FALSE,0.0);     /* Fails on invalid day */
  ST2DT(1,1,-1,0,0,0,0,FALSE,0.0);        /* Fails on invalid year */
  ST2DT(1,1,10000,0,0,0,0,FALSE,0.0);     /* Fails on invalid year */
  ST2DT(1,1,9999,0,0,0,0,TRUE,2958101.0); /* 9999 is last valid year */
  ST2DT(31,12,90,0,0,0,0,TRUE,33238.0);   /* 30 <= year < 100 is 1900+year */
  ST2DT(1,1,30,0,0,0,0,TRUE,10959.0);     /* 30 <= year < 100 is 1900+year */
  ST2DT(1,1,29,0,0,0,0,TRUE,47119.0);     /* 0 <= year < 30 is 2000+year */
  ST2DT(1,1,0,0,0,0,0,TRUE,36526.0);      /* 0 <= year < 30 is 2000+year */
}