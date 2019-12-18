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
struct sway_output {int dummy; } ;
typedef  enum sway_container_layout { ____Placeholder_sway_container_layout } sway_container_layout ;

/* Variables and functions */
 int L_HORIZ ; 
 int L_NONE ; 
 int L_STACKED ; 
 int L_TABBED ; 
 int L_VERT ; 
 int parse_layout_string (char*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int toggle_split_layout (int,int,struct sway_output*) ; 

__attribute__((used)) static enum sway_container_layout get_layout_toggle(int argc, char **argv,
		enum sway_container_layout layout,
		enum sway_container_layout prev_split_layout,
		struct sway_output *output) {
	// "layout toggle"
	if (argc == 1) {
		return toggle_split_layout(layout, prev_split_layout, output);
	}

	if (argc == 2) {
		// "layout toggle split" (same as "layout toggle")
		if (strcasecmp(argv[1], "split") == 0) {
			return toggle_split_layout(layout, prev_split_layout, output);
		}
		// "layout toggle all"
		if (strcasecmp(argv[1], "all") == 0) {
			return layout == L_HORIZ ? L_VERT :
				layout == L_VERT ? L_STACKED :
				layout == L_STACKED ? L_TABBED : L_HORIZ;
		}
		return L_NONE;
	}

	enum sway_container_layout parsed;
	int curr = 1;
	for (; curr < argc; curr++) {
		parsed = parse_layout_string(argv[curr]);
		if (parsed == layout || (strcmp(argv[curr], "split") == 0 &&
				 (layout == L_VERT || layout == L_HORIZ))) {
			break;
		}
	}
	for (int i = curr + 1; i != curr; ++i) {
		// cycle round to find next valid layout
		if (i >= argc) {
			i = 1;
		}
		parsed = parse_layout_string(argv[i]);
		if (parsed != L_NONE) {
			return parsed;
		}
		if (strcmp(argv[i], "split") == 0) {
			return toggle_split_layout(layout, prev_split_layout, output);
		}
		// invalid layout strings are silently ignored
	}
	return L_NONE;
}