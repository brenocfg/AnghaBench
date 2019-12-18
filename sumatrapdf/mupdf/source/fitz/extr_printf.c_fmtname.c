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
typedef  size_t c ;

/* Variables and functions */
 int /*<<< orphan*/  fmtputc (struct fmtbuf*,int) ; 

__attribute__((used)) static void fmtname(struct fmtbuf *out, const char *s)
{
	int c;
	fmtputc(out, '/');
	while ((c = *s++) != 0) {
		if (c <= 32 || c == '/' || c == '#') {
			fmtputc(out, '#');
			fmtputc(out, "0123456789ABCDEF"[(c>>4)&15]);
			fmtputc(out, "0123456789ABCDEF"[(c)&15]);
		} else {
			fmtputc(out, c);
		}
	}
}