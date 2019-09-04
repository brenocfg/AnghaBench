#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct view {size_t lines; TYPE_2__* line; } ;
struct reference {int /*<<< orphan*/  title; int /*<<< orphan*/  time; int /*<<< orphan*/  author; TYPE_1__* ref; int /*<<< orphan*/  member_0; } ;
struct buffer {char* data; } ;
struct TYPE_4__ {int dirty; struct reference* data; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 char* io_memchr (struct buffer*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_author_line (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  string_expand (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  view_column_info_update (struct view*,TYPE_2__*) ; 

__attribute__((used)) static bool
refs_read(struct view *view, struct buffer *buf, bool force_stop)
{
	struct reference template = {0};
	char *author;
	char *title;
	size_t i;

	if (!buf)
		return true;

	if (!*buf->data)
		return false;

	author = io_memchr(buf, buf->data, 0);
	title = io_memchr(buf, author, 0);

	if (author)
		parse_author_line(author, &template.author, &template.time);

	for (i = 0; i < view->lines; i++) {
		struct reference *reference = view->line[i].data;

		if (strcmp(reference->ref->id, buf->data))
			continue;

		reference->author = template.author;
		reference->time = template.time;

		if (title)
			string_expand(reference->title, sizeof(reference->title), title, strlen(title), 1);

		view->line[i].dirty = true;
		view_column_info_update(view, &view->line[i]);
	}

	return true;
}