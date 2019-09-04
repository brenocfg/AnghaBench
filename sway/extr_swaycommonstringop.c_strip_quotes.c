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
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 char* strchr (char*,int /*<<< orphan*/ ) ; 

void strip_quotes(char *str) {
	bool in_str = false;
	bool in_chr = false;
	bool escaped = false;
	char *end = strchr(str,0);
	while (*str) {
		if (*str == '\'' && !in_str && !escaped) {
			in_chr = !in_chr;
			goto shift_over;
		} else if (*str == '\"' && !in_chr && !escaped) {
			in_str = !in_str;
			goto shift_over;
		} else if (*str == '\\') {
			escaped = !escaped;
			++str;
			continue;
		}
		escaped = false;
		++str;
		continue;
		shift_over:
		memmove(str, str+1, end-- - str);
	}
	*end = '\0';
}