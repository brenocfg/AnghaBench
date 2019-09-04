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
 char ascii_tolower (char const) ; 
 scalar_t__ string_enum_sep (char) ; 

bool
enum_name_copy(char buf[], size_t bufsize, const char *name)
{
	int bufpos;

	for (bufpos = 0; name[bufpos] && bufpos < bufsize - 1; bufpos++) {
		buf[bufpos] = ascii_tolower(name[bufpos]);
		if (string_enum_sep(buf[bufpos]))
			buf[bufpos] = '-';
	}

	buf[bufpos] = 0;
	return bufpos < bufsize;
}