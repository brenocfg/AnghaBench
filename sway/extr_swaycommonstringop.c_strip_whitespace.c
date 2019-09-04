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
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 size_t strlen (char*) ; 
 size_t strspn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  whitespace ; 

void strip_whitespace(char *str) {
	size_t len = strlen(str);
	size_t start = strspn(str, whitespace);
	memmove(str, &str[start], len + 1 - start);

	if (*str) {
		for (len -= start + 1; isspace(str[len]); --len) {}
		str[len + 1] = '\0';
	}
}