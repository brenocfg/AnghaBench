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
typedef  char u_char ;

/* Variables and functions */
 int EOF ; 

__attribute__((used)) static int
cmd_string_getc(const char *s, size_t *p)
{
	const u_char	*ucs = s;

	if (ucs[*p] == '\0')
		return (EOF);
	return (ucs[(*p)++]);
}