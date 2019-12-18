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
typedef  int /*<<< orphan*/  uint64_t ;
struct fmtbuf {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  fmtuint64 (struct fmtbuf*,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void fmtint64(struct fmtbuf *out, int64_t value, int s, int z, int w, int base)
{
	uint64_t a;

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
	fmtuint64(out, a, s, z, w, base);
}