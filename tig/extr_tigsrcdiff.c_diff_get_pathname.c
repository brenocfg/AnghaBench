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
struct view {int dummy; } ;
struct line {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  LINE_DIFF_ADD_FILE ; 
 int /*<<< orphan*/  LINE_DIFF_HEADER ; 
 int /*<<< orphan*/  STRING_SIZE (char*) ; 
 char* box_text (struct line*) ; 
 struct line* find_next_line_by_type (struct view*,struct line*,int /*<<< orphan*/ ) ; 
 struct line* find_prev_line_by_type (struct view*,struct line*,int /*<<< orphan*/ ) ; 
 scalar_t__ opt_diff_noprefix ; 
 int /*<<< orphan*/  prefixcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 char* strstr (char*,char const*) ; 

const char *
diff_get_pathname(struct view *view, struct line *line)
{
	struct line *header;
	const char *dst;
	const char *prefixes[] = { "diff --cc ", "diff --combined " };
	const char *name;
	int i;

	header = find_prev_line_by_type(view, line, LINE_DIFF_HEADER);
	if (!header)
		return NULL;

	for (i = 0; i < ARRAY_SIZE(prefixes); i++) {
		dst = strstr(box_text(header), prefixes[i]);
		if (dst)
			return dst + strlen(prefixes[i]);
	}

	header = find_next_line_by_type(view, header, LINE_DIFF_ADD_FILE);
	if (!header)
		return NULL;

	name = box_text(header);
	if (!prefixcmp(name, "+++ "))
		name += STRING_SIZE("+++ ");

	if (opt_diff_noprefix)
		return name;

	/* Handle mnemonic prefixes, such as "b/" and "w/". */
	if (!prefixcmp(name, "b/") || !prefixcmp(name, "w/"))
		name += STRING_SIZE("b/");
	return name;
}