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
typedef  size_t u_int ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static const char *
cmd_find_map_table(const char *table[][2], const char *s)
{
	u_int	i;

	for (i = 0; table[i][0] != NULL; i++) {
		if (strcmp(s, table[i][0]) == 0)
			return (table[i][1]);
	}
	return (s);
}