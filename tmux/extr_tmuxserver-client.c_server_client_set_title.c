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
struct session {int /*<<< orphan*/  options; } ;
struct format_tree {int dummy; } ;
struct client {char* title; int /*<<< orphan*/  tty; struct session* session; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORMAT_NONE ; 
 struct format_tree* format_create (struct client*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_defaults (struct format_tree*,struct client*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* format_expand_time (struct format_tree*,char const*) ; 
 int /*<<< orphan*/  format_free (struct format_tree*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* options_get_string (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  tty_set_title (int /*<<< orphan*/ *,char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
server_client_set_title(struct client *c)
{
	struct session		*s = c->session;
	const char		*template;
	char			*title;
	struct format_tree	*ft;

	template = options_get_string(s->options, "set-titles-string");

	ft = format_create(c, NULL, FORMAT_NONE, 0);
	format_defaults(ft, c, NULL, NULL, NULL);

	title = format_expand_time(ft, template);
	if (c->title == NULL || strcmp(title, c->title) != 0) {
		free(c->title);
		c->title = xstrdup(title);
		tty_set_title(&c->tty, c->title);
	}
	free(title);

	format_free(ft);
}