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
struct format_tree {int dummy; } ;
struct client {char* prompt_string; char* prompt_buffer; int /*<<< orphan*/  flags; scalar_t__ prompt_hindex; int /*<<< orphan*/  prompt_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_REDRAWSTATUS ; 
 int /*<<< orphan*/  FORMAT_NONE ; 
 struct format_tree* format_create (struct client*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_defaults (struct format_tree*,struct client*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* format_expand_time (struct format_tree*,char const*) ; 
 int /*<<< orphan*/  format_free (struct format_tree*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* utf8_fromcstr (char*) ; 
 int /*<<< orphan*/  utf8_strlen (char*) ; 

void
status_prompt_update(struct client *c, const char *msg, const char *input)
{
	struct format_tree	*ft;
	char			*tmp;

	ft = format_create(c, NULL, FORMAT_NONE, 0);
	format_defaults(ft, c, NULL, NULL, NULL);

	tmp = format_expand_time(ft, input);

	free(c->prompt_string);
	c->prompt_string = format_expand_time(ft, msg);

	free(c->prompt_buffer);
	c->prompt_buffer = utf8_fromcstr(tmp);
	c->prompt_index = utf8_strlen(c->prompt_buffer);

	c->prompt_hindex = 0;

	c->flags |= CLIENT_REDRAWSTATUS;

	free(tmp);
	format_free(ft);
}