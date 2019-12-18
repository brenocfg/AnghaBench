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
struct ft_error {char const* str; int err; } ;

/* Variables and functions */
 struct ft_error* ft_errors ; 

const char *ft_error_string(int err)
{
	const struct ft_error *e;

	for (e = ft_errors; e->str; e++)
		if (e->err == err)
			return e->str;

	return "Unknown error";
}