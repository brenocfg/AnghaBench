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
 size_t SIZEOF_REV ; 
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/  string_ncopy_do (char*,size_t,char const*,size_t) ; 

void
string_copy_rev(char *dst, const char *src)
{
	size_t srclen;

	if (!*src)
		return;

	for (srclen = 0; srclen < SIZEOF_REV; srclen++)
		if (!src[srclen] || isspace(src[srclen]))
			break;

	string_ncopy_do(dst, SIZEOF_REV, src, srclen);
}