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
 int /*<<< orphan*/  DT2UD (double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  VAR_VALIDDATE ; 
 int /*<<< orphan*/  VarUdateFromDate ; 

__attribute__((used)) static void test_VarUdateFromDate(void)
{
  CHECKPTR(VarUdateFromDate);
  DT2UD(29221.0,0,S_OK,1,1,1980,0,0,0,0,2,1);        /* 1 Jan 1980 */
  DT2UD(29222.0,0,S_OK,2,1,1980,0,0,0,0,3,2);        /* 2 Jan 1980 */
  DT2UD(33238.0,0,S_OK,31,12,1990,0,0,0,0,1,365);    /* 31 Dec 1990 */
  DT2UD(0.0,0,S_OK,30,12,1899,0,0,0,0,6,364);        /* 30 Dec 1899 - VT_DATE 0.0 */
  DT2UD(-657434.0,0,S_OK,1,1,100,0,0,0,0,5,1);       /* 1 Jan 100 - Min */
  DT2UD(-657435.0,0,E_INVALIDARG,0,0,0,0,0,0,0,0,0); /* < 1 Jan 100 => err */
  DT2UD(2958465.0,0,S_OK,31,12,9999,0,0,0,0,5,365);  /* 31 Dec 9999 - Max */
  DT2UD(2958466.0,0,E_INVALIDARG,0,0,0,0,0,0,0,0,0); /* > 31 Dec 9999 => err  */

  /* VAR_VALIDDATE doesn't prevent upper and lower bounds being checked */
  DT2UD(-657435.0,VAR_VALIDDATE,E_INVALIDARG,0,0,0,0,0,0,0,0,0);
  DT2UD(2958466.0,VAR_VALIDDATE,E_INVALIDARG,0,0,0,0,0,0,0,0,0);

  /* Times */
  DT2UD(29221.25,0,S_OK,1,1,1980,6,0,0,0,2,1);           /* 6 AM */
  DT2UD(29221.33333333,0,S_OK,1,1,1980,8,0,0,0,2,1);     /* 8 AM */
  DT2UD(29221.5,0,S_OK,1,1,1980,12,0,0,0,2,1);           /* 12 AM */
  DT2UD(29221.9888884444,0,S_OK,1,1,1980,23,44,0,0,2,1); /* 11:44 PM */
  DT2UD(29221.7508765432,0,S_OK,1,1,1980,18,1,16,0,2,1); /* 6:18:02 PM */

  /* Test handling of times on dates prior to the epoch */
  DT2UD(-5.25,0,S_OK,25,12,1899,6,0,0,0,1,359);
  DT2UD(-5.9999884259259,0,S_OK,25,12,1899,23,59,59,0,1,359);
  /* This just demonstrates the non-linear nature of values prior to the epoch */
  DT2UD(-4.0,0,S_OK,26,12,1899,0,0,0,0,2,360);
  /* Numerical oddity: for 0.0 < x < 1.0, x and -x represent the same datetime */
  DT2UD(-0.25,0,S_OK,30,12,1899,6,0,0,0,6,364);
  DT2UD(0.25,0,S_OK,30,12,1899,6,0,0,0,6,364);
}