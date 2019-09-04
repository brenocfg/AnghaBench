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
 scalar_t__ isdigit (char const) ; 

size_t
parse_size(const char *text)
{
	size_t size = 0;

	while (*text == ' ')
		text++;

	while (isdigit(*text))
		size = (size * 10) + (*text++ - '0');

	return size;
}