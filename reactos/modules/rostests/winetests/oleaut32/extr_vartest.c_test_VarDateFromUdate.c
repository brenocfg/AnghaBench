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
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  UD2T (int,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,double) ; 
 int VAR_DATEVALUEONLY ; 
 int VAR_TIMEVALUEONLY ; 
 int /*<<< orphan*/  VarDateFromUdate ; 

__attribute__((used)) static void test_VarDateFromUdate(void)
{
  CHECKPTR(VarDateFromUdate);
  UD2T(1,1,1980,0,0,0,0,2,1,0,S_OK,29221.0);      /* 1 Jan 1980 */
  UD2T(2,1,1980,0,0,0,0,3,2,0,S_OK,29222.0);      /* 2 Jan 1980 */
  UD2T(2,1,1980,0,0,0,0,4,5,0,S_OK,29222.0);      /* 2 Jan 1980 */
  UD2T(31,12,1990,0,0,0,0,0,0,0,S_OK,33238.0);    /* 31 Dec 1990 */
  UD2T(31,12,90,0,0,0,0,0,0,0,S_OK,33238.0);      /* year < 100 is 1900+year! */
  UD2T(30,12,1899,0,0,0,0,6,364,0,S_OK,0.0);      /* 30 Dec 1899 - VT_DATE 0.0 */
  UD2T(1,1,100,0,0,0,0,0,0,0,S_OK,-657434.0);     /* 1 Jan 100 - Min */
  UD2T(31,12,9999,0,0,0,0,0,0,0,S_OK,2958465.0);  /* 31 Dec 9999 - Max */
  UD2T(1,1,10000,0,0,0,0,0,0,0,E_INVALIDARG,0.0); /* > 31 Dec 9999 => err  */
  UD2T(1,1,-10000,0,0,0,0,0,0,0,E_INVALIDARG,0.0);/* < -9999 => err  */

  UD2T(30,12,1899,0,0,0,0,0,0,0,S_OK,0.0); /* 30 Dec 1899 0:00:00  */
  UD2T(30,12,1899,0,0,0,999,0,0,0,S_OK,0.0); /* Ignore milliseconds  */

  UD2T(1,1,1980,18,1,16,0,2,1,0,S_OK,29221.75087962963);             /* 6:18:02 PM */
  UD2T(1,300,1980,18,1,16,0,2,1,0,S_OK,38322.75087962963);           /* Test fwdrolled month */
  UD2T(300,1,1980,18,1,16,0,2,1,0,S_OK,29520.75087962963);           /* Test fwdrolled days */
  UD2T(0,1,1980,42,1,16,0,2,1,0,S_OK,29221.75087962963);             /* Test fwdrolled hours */
  UD2T(1,1,1980,17,61,16,0,2,1,0,S_OK,29221.75087962963);            /* Test fwdrolled minutes */
  UD2T(1,1,1980,18,0,76,0,2,1,0,S_OK,29221.75087962963);             /* Test fwdrolled seconds */
  UD2T(1,-300,1980,18,1,16,0,2,1,0,S_OK,20059.75087962963);          /* Test backrolled month */
  UD2T(-300,1,1980,18,1,16,0,2,1,0,S_OK,28920.75087962963);          /* Test backrolled days */
  UD2T(3,1,1980,-30,1,16,0,2,1,0,S_OK,29221.75087962963);            /* Test backrolled hours */
  UD2T(1,1,1980,20,-119,16,0,2,1,0,S_OK,29221.75087962963);          /* Test backrolled minutes */
  UD2T(1,1,1980,18,3,-104,0,2,1,0,S_OK,29221.75087962963);           /* Test backrolled seconds */
  UD2T(1,12001,-1020,18,1,16,0,0,0,0,S_OK,29221.75087962963);        /* Test rolled year and month */
  UD2T(1,-23,1982,18,1,16,0,0,0,0,S_OK,29221.75087962963);           /* Test backrolled month */
  UD2T(-59,3,1980,18,1,16,0,0,0,0,S_OK,29221.75087962963);           /* Test backrolled days */
  UD2T(1,1,0,0,0,0,0,0,0,0,S_OK,36526);                              /* Test zero year */
  UD2T(0,0,1980,0,0,0,0,0,0,0,S_OK,29189);                           /* Test zero day and month */
  UD2T(0,1,1980,0,0,0,0,2,1,0,S_OK,29220.0);                         /* Test zero day = LastDayOfMonth */
  UD2T(-1,1,1980,18,1,16,0,0,0,0,S_OK,29219.75087962963);            /* Test day -1 = LastDayOfMonth - 1 */
  UD2T(1,1,-1,18,1,16,0,0,0,0,S_OK,36161.75087962963);               /* Test year -1 = 1999 */
  UD2T(1,-1,1980,18,1,16,0,0,0,0,S_OK,29160.7508796296);             /* Test month -1 = 11 */
  UD2T(1,13,1980,0,0,0,0,2,1,0,S_OK,29587.0);                        /* Rolls fwd to 1/1/1981 */

  /* Test handling of times on dates prior to the epoch */
  UD2T(25,12,1899,6,0,0,0,1,359,0,S_OK,-5.25);
  UD2T(25,12,1899,23,59,59,0,1,359,0,S_OK,-5.9999884259259);
  /* This just demonstrates the non-linear nature of values prior to the epoch */
  UD2T(26,12,1899,0,0,0,0,2,360,0,S_OK,-4.0);
  /* for DATE values 0.0 < x < 1.0, x and -x represent the same datetime */
  /* but when converting to DATE, prefer the positive versions */
  UD2T(30,12,1899,6,0,0,0,6,364,0,S_OK,0.25);

  UD2T(1,1,1980,18,1,16,0,2,1,VAR_TIMEVALUEONLY,S_OK,0.7508796296296296);
  UD2T(1,1,1980,18,1,16,0,2,1,VAR_DATEVALUEONLY,S_OK,29221.0);
  UD2T(25,12,1899,6,0,0,0,1,359,VAR_TIMEVALUEONLY,S_OK,0.25);
  UD2T(25,12,1899,6,0,0,0,1,359,VAR_DATEVALUEONLY,S_OK,-5.0);
  UD2T(1,-1,1980,18,1,16,0,0,0,VAR_TIMEVALUEONLY|VAR_DATEVALUEONLY,S_OK,0.7508796296296296);
}