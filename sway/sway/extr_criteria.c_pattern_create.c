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
struct pattern {int /*<<< orphan*/  regex; int /*<<< orphan*/  match_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PATTERN_FOCUSED ; 
 int /*<<< orphan*/  PATTERN_PCRE ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 struct pattern* calloc (int,int) ; 
 int /*<<< orphan*/  generate_regex (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool pattern_create(struct pattern **pattern, char *value) {
	*pattern = calloc(1, sizeof(struct pattern));
	if (!*pattern) {
		sway_log(SWAY_ERROR, "Failed to allocate pattern");
	}

	if (strcmp(value, "__focused__") == 0) {
		(*pattern)->match_type = PATTERN_FOCUSED;
	} else {
		(*pattern)->match_type = PATTERN_PCRE;
		if (!generate_regex(&(*pattern)->regex, value)) {
			return false;
		};
	}
	return true;
}