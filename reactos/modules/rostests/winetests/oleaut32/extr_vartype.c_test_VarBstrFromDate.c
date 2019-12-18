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
 int /*<<< orphan*/  BSTR_DATE (double,char*) ; 

__attribute__((used)) static void test_VarBstrFromDate(void)
{
#define BSTR_DATE(dt,str) _BSTR_DATE(dt,str,__LINE__)

  BSTR_DATE(0.0, "12:00:00 AM");
  BSTR_DATE(3.34, "1/2/1900 8:09:36 AM");
  BSTR_DATE(3339.34, "2/20/1909 8:09:36 AM");
  BSTR_DATE(365.00, "12/30/1900");
  BSTR_DATE(365.25, "12/30/1900 6:00:00 AM");
  BSTR_DATE(1461.0, "12/31/1903");
  BSTR_DATE(1461.5, "12/31/1903 12:00:00 PM");
  BSTR_DATE(-49192.24, "4/24/1765 5:45:36 AM");
  BSTR_DATE(-657434.0, "1/1/100");
  BSTR_DATE(2958465.0, "12/31/9999");

#undef BSTR_DATE
}