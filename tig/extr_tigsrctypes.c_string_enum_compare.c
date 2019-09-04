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
 scalar_t__ ascii_toupper (char const) ; 
 scalar_t__ string_enum_sep (char const) ; 

int
string_enum_compare(const char *str1, const char *str2, int len)
{
	size_t i;

	/* Diff-Header == DIFF_HEADER */
	for (i = 0; i < len; i++) {
		if (ascii_toupper(str1[i]) == ascii_toupper(str2[i]))
			continue;

		if (string_enum_sep(str1[i]) &&
		    string_enum_sep(str2[i]))
			continue;

		return str1[i] - str2[i];
	}

	return 0;
}