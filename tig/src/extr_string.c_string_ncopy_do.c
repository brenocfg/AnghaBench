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
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

void
string_ncopy_do(char *dst, size_t dstlen, const char *src, size_t srclen)
{
	if (srclen > dstlen - 1)
		srclen = dstlen - 1;

	strncpy(dst, src, srclen);
	dst[srclen] = 0;
}