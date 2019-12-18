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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 size_t INT_MAX ; 
 int /*<<< orphan*/  fatalx (char*) ; 
 int vsnprintf (char*,size_t,char const*,int /*<<< orphan*/ ) ; 

int
xvsnprintf(char *str, size_t len, const char *fmt, va_list ap)
{
	int i;

	if (len > INT_MAX)
		fatalx("xsnprintf: len > INT_MAX");

	i = vsnprintf(str, len, fmt, ap);

	if (i < 0 || i >= (int)len)
		fatalx("xsnprintf: overflow");

	return i;
}