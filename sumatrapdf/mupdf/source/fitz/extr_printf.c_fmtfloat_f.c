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
struct fmtbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fmtputc (struct fmtbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,double) ; 

__attribute__((used)) static void fmtfloat_f(struct fmtbuf *out, double f, int w, int p)
{
	char buf[100], *s = buf;
	snprintf(buf, sizeof buf, "%*.*f", w, p, f);
	while (*s)
		fmtputc(out, *s++);
}