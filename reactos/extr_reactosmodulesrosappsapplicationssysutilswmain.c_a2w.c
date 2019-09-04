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
typedef  scalar_t__ wchar_t ;

/* Variables and functions */

wchar_t *
a2w( char * a, wchar_t * w )
{
	wchar_t * ww = w;
	while (*a) *w++ = (wchar_t) *a++;
	*w = 0;
	return ww;
}