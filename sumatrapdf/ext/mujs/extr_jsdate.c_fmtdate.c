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
 int DateFromTime (double) ; 
 int MonthFromTime (double) ; 
 int YearFromTime (double) ; 
 int /*<<< orphan*/  isfinite (double) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 

__attribute__((used)) static char *fmtdate(char *buf, double t)
{
	int y = YearFromTime(t);
	int m = MonthFromTime(t);
	int d = DateFromTime(t);
	if (!isfinite(t))
		return "Invalid Date";
	sprintf(buf, "%04d-%02d-%02d", y, m+1, d);
	return buf;
}