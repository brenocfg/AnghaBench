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
 char* malloc (int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  sway_assert (int,char*) ; 

char *join_args(char **argv, int argc) {
	if (!sway_assert(argc > 0, "argc should be positive")) {
		return NULL;
	}
	int len = 0, i;
	for (i = 0; i < argc; ++i) {
		len += strlen(argv[i]) + 1;
	}
	char *res = malloc(len);
	len = 0;
	for (i = 0; i < argc; ++i) {
		strcpy(res + len, argv[i]);
		len += strlen(argv[i]);
		res[len++] = ' ';
	}
	res[len - 1] = '\0';
	return res;
}