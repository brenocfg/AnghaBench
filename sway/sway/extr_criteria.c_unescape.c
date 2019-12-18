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
 char* calloc (scalar_t__,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void unescape(char *value) {
	if (!strchr(value, '\\')) {
		return;
	}
	char *copy = calloc(strlen(value) + 1, 1);
	char *readhead = value;
	char *writehead = copy;
	while (*readhead) {
		if (*readhead == '\\' && *(readhead + 1) == '"') {
			// skip the slash
			++readhead;
		}
		*writehead = *readhead;
		++writehead;
		++readhead;
	}
	strcpy(value, copy);
	free(copy);
}