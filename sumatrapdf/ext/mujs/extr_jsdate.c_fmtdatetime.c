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
 int /*<<< orphan*/  fmtdate (char*,double) ; 
 int /*<<< orphan*/  fmttime (char*,double,double) ; 
 int /*<<< orphan*/  isfinite (double) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 

__attribute__((used)) static char *fmtdatetime(char *buf, double t, double tza)
{
	char dbuf[20], tbuf[20];
	if (!isfinite(t))
		return "Invalid Date";
	fmtdate(dbuf, t);
	fmttime(tbuf, t, tza);
	sprintf(buf, "%sT%s", dbuf, tbuf);
	return buf;
}