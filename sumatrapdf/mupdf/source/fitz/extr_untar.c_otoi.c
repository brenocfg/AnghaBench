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
typedef  int int64_t ;

/* Variables and functions */
 scalar_t__ isoctdigit (char const) ; 

__attribute__((used)) static inline int64_t otoi(const char *s)
{
	int64_t value = 0;

	while (*s && isoctdigit(*s))
	{
		value *= 8;
		value += (*s) - '0';
		s++;
	}

	return value;
}