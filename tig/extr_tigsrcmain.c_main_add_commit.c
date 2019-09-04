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
struct view {struct main_state* private; } ;
struct main_state {scalar_t__* reflogmsg; } ;
struct line {int dummy; } ;
struct commit {int /*<<< orphan*/  title; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int SIZEOF_STR ; 
 struct line* add_line_alloc (struct view*,struct commit**,int,size_t,int) ; 
 int /*<<< orphan*/  memset (struct commit*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  string_expand (char*,int,char const*,size_t,int) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  view_column_info_update (struct view*,struct line*) ; 

__attribute__((used)) static struct commit *
main_add_commit(struct view *view, enum line_type type, struct commit *template,
		const char *title, bool custom)
{
	struct main_state *state = view->private;
	size_t titlelen;
	struct commit *commit;
	char buf[SIZEOF_STR / 2];
	struct line *line;

	/* FIXME: More graceful handling of titles; append "..." to
	 * shortened titles, etc. */
	string_expand(buf, sizeof(buf), title, strlen(title), 1);
	title = buf;
	titlelen = strlen(title);

	line = add_line_alloc(view, &commit, type, titlelen, custom);
	if (!line)
		return NULL;

	*commit = *template;
	strncpy(commit->title, title, titlelen);
	memset(template, 0, sizeof(*template));
	state->reflogmsg[0] = 0;

	view_column_info_update(view, line);
	return commit;
}