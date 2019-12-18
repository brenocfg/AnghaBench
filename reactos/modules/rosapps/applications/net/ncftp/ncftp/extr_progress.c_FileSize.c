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
 double kGigabyte ; 
 double kKilobyte ; 
 double kMegabyte ; 
 double kTerabyte ; 

double
FileSize(const double size, const char **uStr0, double *const uMult0)
{
	double uMult, uTotal;
	const char *uStr;

	/* The comparisons below may look odd, but the reason
	 * for them is that we only want a maximum of 3 digits
	 * before the decimal point.  (I.e., we don't want to
	 * see "1017.2 kB", instead we want "0.99 MB".
	 */
	if (size > (999.5 * kGigabyte)) {
		uStr = "TB";
		uMult = kTerabyte;
	} else if (size > (999.5 * kMegabyte)) {
		uStr = "GB";
		uMult = kGigabyte;
	} else if (size > (999.5 * kKilobyte)) {
		uStr = "MB";
		uMult = kMegabyte;
	} else if (size > 999.5) {
		uStr = "kB";
		uMult = 1024;
	} else {
		uStr = "B";
		uMult = 1;
	}
	if (uStr0 != NULL)
		*uStr0 = uStr;
	if (uMult0 != NULL)
		*uMult0 = uMult;
	uTotal = size / ((double) uMult);
	if (uTotal < 0.0)
		uTotal = 0.0;
	return (uTotal);
}