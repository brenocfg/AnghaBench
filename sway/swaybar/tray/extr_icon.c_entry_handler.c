#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct icon_theme_subdir {char* name; int size; int max_size; int min_size; int threshold; int /*<<< orphan*/  type; } ;
struct icon_theme {TYPE_1__* subdirs; int /*<<< orphan*/  directories; void* inherits; void* comment; void* name; } ;
struct TYPE_2__ {int length; struct icon_theme_subdir** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIXED ; 
 int /*<<< orphan*/  SCALABLE ; 
 int /*<<< orphan*/  THRESHOLD ; 
 int /*<<< orphan*/  split_string (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 void* strdup (char*) ; 
 int strtol (char*,char**,int) ; 

__attribute__((used)) static int entry_handler(char *group, char *key, char *value,
		struct icon_theme *theme) {
	if (strcmp(group, "Icon Theme") == 0) {
		if (strcmp(key, "Name") == 0) {
			theme->name = strdup(value);
		} else if (strcmp(key, "Comment") == 0) {
			theme->comment = strdup(value);
		} else if (strcmp(key, "Inherits") == 0) {
			theme->inherits = strdup(value);
		} else if (strcmp(key, "Directories") == 0) {
			theme->directories = split_string(value, ",");
		} // Ignored: ScaledDirectories, Hidden, Example
	} else {
		if (theme->subdirs->length == 0) { // skip
			return false;
		}

		struct icon_theme_subdir *subdir =
			theme->subdirs->items[theme->subdirs->length - 1];
		if (strcmp(subdir->name, group) != 0) { // skip
			return false;
		}

		char *end;
		int n = strtol(value, &end, 10);
		if (strcmp(key, "Size") == 0) {
			subdir->size = n;
			return *end != '\0';
		} else if (strcmp(key, "Type") == 0) {
			if (strcmp(value, "Fixed") == 0) {
				subdir->type = FIXED;
			} else if (strcmp(value, "Scalable") == 0) {
				subdir->type = SCALABLE;
			} else if (strcmp(value, "Threshold") == 0) {
				subdir->type = THRESHOLD;
			} else {
				return true;
			}
		} else if (strcmp(key, "MaxSize") == 0) {
			subdir->max_size = n;
			return *end != '\0';
		} else if (strcmp(key, "MinSize") == 0) {
			subdir->min_size = n;
			return *end != '\0';
		} else if (strcmp(key, "Threshold") == 0) {
			subdir->threshold = n;
			return *end != '\0';
		} // Ignored: Scale, Applications
	}
	return false;
}