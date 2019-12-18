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
struct icon_theme_subdir {int size; int type; int max_size; int min_size; int threshold; int /*<<< orphan*/  name; } ;
struct icon_theme {TYPE_1__* subdirs; int /*<<< orphan*/  directories; } ;
struct TYPE_2__ {int length; struct icon_theme_subdir** items; } ;

/* Variables and functions */
#define  FIXED 130 
#define  SCALABLE 129 
#define  THRESHOLD 128 
 struct icon_theme_subdir* calloc (int,int) ; 
 int /*<<< orphan*/  cmp_group ; 
 int /*<<< orphan*/  list_add (TYPE_1__*,struct icon_theme_subdir*) ; 
 int list_seq_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  validate_icon_theme (struct icon_theme*) ; 

__attribute__((used)) static bool group_handler(char *old_group, char *new_group,
		struct icon_theme *theme) {
	if (!old_group) { // first group must be "Icon Theme"
		return strcmp(new_group, "Icon Theme");
	}

	if (strcmp(old_group, "Icon Theme") == 0) {
		if (!validate_icon_theme(theme)) {
			return true;
		}
	} else {
		if (theme->subdirs->length == 0) { // skip
			return false;
		}

		struct icon_theme_subdir *subdir =
			theme->subdirs->items[theme->subdirs->length - 1];
		if (!subdir->size) return true;

		switch (subdir->type) {
		case FIXED: subdir->max_size = subdir->min_size = subdir->size;
			break;
		case SCALABLE: {
			if (!subdir->max_size) subdir->max_size = subdir->size;
			if (!subdir->min_size) subdir->min_size = subdir->size;
			break;
		}
		case THRESHOLD:
			subdir->max_size = subdir->size + subdir->threshold;
			subdir->min_size = subdir->size - subdir->threshold;
		}
	}

	if (new_group && list_seq_find(theme->directories, cmp_group, new_group) != -1) {
		struct icon_theme_subdir *subdir = calloc(1, sizeof(struct icon_theme_subdir));
		if (!subdir) {
			return true;
		}
		subdir->name = strdup(new_group);
		subdir->threshold = 2;
		list_add(theme->subdirs, subdir);
	}

	return false;
}