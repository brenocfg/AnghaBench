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

__attribute__((used)) static void fmtquote(struct fmtbuf *out, const char *s, int sq, int eq)
{
	int c;
	fmtputc(out, sq);
	while ((c = *s++) != 0) {
		switch (c) {
		default:
			if (c < 32 || c > 127) {
				fmtputc(out, '\\');
				if (sq == '(')
				{
					fmtputc(out, '0' + ((c >> 6) & 7));
					fmtputc(out, '0' + ((c >> 3) & 7));
					fmtputc(out, '0' + ((c) & 7));
				}
				else
				{
					fmtputc(out, 'x');
					fmtputc(out, "0123456789ABCDEF"[(c>>4)&15]);
					fmtputc(out, "0123456789ABCDEF"[(c)&15]);
				}
			} else {
				if (c == sq || c == eq)
					fmtputc(out, '\\');
				fmtputc(out, c);
			}
			break;
		case '\\': fmtputc(out, '\\'); fmtputc(out, '\\'); break;
		case '\b': fmtputc(out, '\\'); fmtputc(out, 'b'); break;
		case '\f': fmtputc(out, '\\'); fmtputc(out, 'f'); break;
		case '\n': fmtputc(out, '\\'); fmtputc(out, 'n'); break;
		case '\r': fmtputc(out, '\\'); fmtputc(out, 'r'); break;
		case '\t': fmtputc(out, '\\'); fmtputc(out, 't'); break;
		}
	}
	fmtputc(out, eq);
}