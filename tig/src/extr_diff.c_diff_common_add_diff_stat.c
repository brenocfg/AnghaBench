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
 struct line* diff_common_read_diff_stat (struct view*,char const*) ; 
 int /*<<< orphan*/  prefixcmp (char const*,char*) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 int strspn (char const*,char*) ; 
 scalar_t__ strstr (char const*,char*) ; 

struct line *
diff_common_add_diff_stat(struct view *view, const char *text, size_t offset)
{
	const char *start = text + offset;
	const char *data = start + strspn(start, " ");
	size_t len = strlen(data);
	char *pipe = strchr(data, '|');

	/* Ensure that '|' is present and the file name part contains
	 * non-space characters. */
	if (!pipe || pipe == data)
		return NULL;

	/* Detect remaining part of a diff stat line:
	 *
	 *	added                    |   40 +++++++++++
	 *	remove                   |  124 --------------------------
	 *	updated                  |   14 +----
	 *	rename.from => rename.to |    0
	 *	.../truncated file name  |   11 ++---
	 *	binary add               |  Bin 0 -> 1234 bytes
	 *	binary update            |  Bin 1234 -> 2345 bytes
	 *	binary copy              |  Bin
	 *	unmerged                 | Unmerged
	 */
	if ((data[len - 1] == '-' || data[len - 1] == '+') ||
	    strstr(pipe, " 0") || strstr(pipe, "Bin") || strstr(pipe, "Unmerged") ||
	    (data[len - 1] == '0' && (strstr(data, "=>") || !prefixcmp(data, "..."))))
		return diff_common_read_diff_stat(view, text);
	return NULL;
}