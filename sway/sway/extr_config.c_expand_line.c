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
 int /*<<< orphan*/  SWAY_ERROR ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*,char const*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *expand_line(const char *block, const char *line, bool add_brace) {
	int size = (block ? strlen(block) + 1 : 0) + strlen(line)
		+ (add_brace ? 2 : 0) + 1;
	char *expanded = calloc(1, size);
	if (!expanded) {
		sway_log(SWAY_ERROR, "Cannot allocate expanded line buffer");
		return NULL;
	}
	snprintf(expanded, size, "%s%s%s%s", block ? block : "",
			block ? " " : "", line, add_brace ? " {" : "");
	return expanded;
}