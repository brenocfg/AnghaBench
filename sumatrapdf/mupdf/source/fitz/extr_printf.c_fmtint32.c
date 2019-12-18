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
 int /*<<< orphan*/  fmtuint32 (struct fmtbuf*,unsigned int,int,int,int,int) ; 

__attribute__((used)) static void fmtint32(struct fmtbuf *out, int value, int s, int z, int w, int base)
{
	unsigned int a;

	if (value < 0)
	{
		s = '-';
		a = -value;
	}
	else if (s)
	{
		s = '+';
		a = value;
	}
	else
	{
		s = 0;
		a = value;
	}
	fmtuint32(out, a, s, z, w, base);
}