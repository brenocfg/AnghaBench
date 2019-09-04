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
struct tree_entry {unsigned long size; int /*<<< orphan*/  id; int /*<<< orphan*/  mode; int /*<<< orphan*/  name; } ;
struct line {int dummy; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;

/* Variables and functions */
 int LINE_HEADER ; 
 struct line* add_line_alloc (struct view*,struct tree_entry**,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  string_copy_rev (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ tree_path_is_parent (char const*) ; 

__attribute__((used)) static struct line *
tree_entry(struct view *view, enum line_type type, const char *path,
	   const char *mode, const char *id, unsigned long size)
{
	bool custom = type == LINE_HEADER || tree_path_is_parent(path);
	struct tree_entry *entry;
	struct line *line = add_line_alloc(view, &entry, type, strlen(path), custom);

	if (!line)
		return NULL;

	strncpy(entry->name, path, strlen(path));
	if (mode)
		entry->mode = strtoul(mode, NULL, 8);
	if (id)
		string_copy_rev(entry->id, id);
	entry->size = size;

	return line;
}