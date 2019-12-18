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
struct view {int /*<<< orphan*/  ref; } ;
struct line {int dummy; } ;

/* Variables and functions */
 char* box_text (struct line*) ; 
 size_t get_graph_indent (char const*) ; 
 int /*<<< orphan*/  string_copy_rev_from_commit_line (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline void
log_copy_rev(struct view *view, struct line *line)
{
	const char *text = box_text(line);
	size_t offset = get_graph_indent(text);

	string_copy_rev_from_commit_line(view->ref, text + offset);
}