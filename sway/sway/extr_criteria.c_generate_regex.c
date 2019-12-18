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
typedef  int /*<<< orphan*/  pcre ;

/* Variables and functions */
 int PCRE_UCP ; 
 int PCRE_UTF8 ; 
 int /*<<< orphan*/  error ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/ * pcre_compile (char*,int,char const**,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char const*,char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static bool generate_regex(pcre **regex, char *value) {
	const char *reg_err;
	int offset;

	*regex = pcre_compile(value, PCRE_UTF8 | PCRE_UCP, &reg_err, &offset, NULL);

	if (!*regex) {
		const char *fmt = "Regex compilation for '%s' failed: %s";
		int len = strlen(fmt) + strlen(value) + strlen(reg_err) - 3;
		error = malloc(len);
		snprintf(error, len, fmt, value, reg_err);
		return false;
	}

	return true;
}