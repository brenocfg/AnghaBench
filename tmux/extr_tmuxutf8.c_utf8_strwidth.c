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
typedef  scalar_t__ u_int ;
struct utf8_data {scalar_t__ size; scalar_t__ width; } ;
typedef  size_t ssize_t ;

/* Variables and functions */

u_int
utf8_strwidth(const struct utf8_data *s, ssize_t n)
{
	ssize_t	i;
	u_int	width;

	width = 0;
	for (i = 0; s[i].size != 0; i++) {
		if (n != -1 && n == i)
			break;
		width += s[i].width;
	}
	return (width);
}