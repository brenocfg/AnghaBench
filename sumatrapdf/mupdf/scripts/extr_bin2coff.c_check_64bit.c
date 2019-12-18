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
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int check_64bit(const char *arg, int *x86_32)
{
	if ((strcmp(arg, "64bit") == 0) || (strcmp(arg, "x64") == 0))
		*x86_32 = 0; /* 0 = 64bit */
	else if ((strcmp(arg, "32bit") == 0) || (strcmp(arg, "Win32") == 0))
		*x86_32 = 1; /* 1 = 32bit */
	else
		return 0;
	return 1;
}