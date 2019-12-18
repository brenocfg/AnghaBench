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
struct view {struct line* line; int /*<<< orphan*/  lines; } ;
struct line {int dirty; struct blame* data; } ;
struct blame_state {int blamed; } ;
struct blame_header {int group; int lineno; scalar_t__ orig_lineno; } ;
struct blame_commit {int dummy; } ;
struct blame {scalar_t__ lineno; struct blame_commit* commit; } ;

/* Variables and functions */
 struct blame_commit* get_blame_commit (struct view*,char const*) ; 
 int /*<<< orphan*/  parse_blame_header (struct blame_header*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct blame_commit *
read_blame_commit(struct view *view, const char *text, struct blame_state *state)
{
	struct blame_header header;
	struct blame_commit *commit;
	struct blame *blame;

	if (!parse_blame_header(&header, text, view->lines))
		return NULL;

	commit = get_blame_commit(view, text);
	if (!commit)
		return NULL;

	state->blamed += header.group;
	while (header.group--) {
		struct line *line = &view->line[header.lineno + header.group - 1];

		blame = line->data;
		blame->commit = commit;
		blame->lineno = header.orig_lineno + header.group - 1;
		line->dirty = 1;
	}

	return commit;
}