#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct format_tree {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct client {int prompt_flags; void* prompt_data; int /*<<< orphan*/  (* prompt_inputcb ) (struct client*,void*,char*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  flags; TYPE_1__ tty; int /*<<< orphan*/  prompt_mode; scalar_t__ prompt_hindex; int /*<<< orphan*/  prompt_freecb; int /*<<< orphan*/  prompt_buffer; int /*<<< orphan*/  prompt_index; void* prompt_string; } ;
typedef  int /*<<< orphan*/  (* prompt_input_cb ) (struct client*,void*,char*,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  prompt_free_cb ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_REDRAWSTATUS ; 
 int /*<<< orphan*/  FORMAT_NONE ; 
 int /*<<< orphan*/  PROMPT_ENTRY ; 
 int PROMPT_INCREMENTAL ; 
 int PROMPT_NOFORMAT ; 
 int TTY_FREEZE ; 
 int TTY_NOCURSOR ; 
 struct format_tree* format_create (struct client*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_defaults (struct format_tree*,struct client*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* format_expand_time (struct format_tree*,char const*) ; 
 int /*<<< orphan*/  format_free (struct format_tree*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  status_message_clear (struct client*) ; 
 int /*<<< orphan*/  status_prompt_clear (struct client*) ; 
 int /*<<< orphan*/  status_push_screen (struct client*) ; 
 int /*<<< orphan*/  stub1 (struct client*,void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utf8_fromcstr (char*) ; 
 int /*<<< orphan*/  utf8_strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char*) ; 
 char* xstrdup (char const*) ; 

void
status_prompt_set(struct client *c, const char *msg, const char *input,
    prompt_input_cb inputcb, prompt_free_cb freecb, void *data, int flags)
{
	struct format_tree	*ft;
	char			*tmp, *cp;

	ft = format_create(c, NULL, FORMAT_NONE, 0);
	format_defaults(ft, c, NULL, NULL, NULL);

	if (input == NULL)
		input = "";
	if (flags & PROMPT_NOFORMAT)
		tmp = xstrdup(input);
	else
		tmp = format_expand_time(ft, input);

	status_message_clear(c);
	status_prompt_clear(c);
	status_push_screen(c);

	c->prompt_string = format_expand_time(ft, msg);

	c->prompt_buffer = utf8_fromcstr(tmp);
	c->prompt_index = utf8_strlen(c->prompt_buffer);

	c->prompt_inputcb = inputcb;
	c->prompt_freecb = freecb;
	c->prompt_data = data;

	c->prompt_hindex = 0;

	c->prompt_flags = flags;
	c->prompt_mode = PROMPT_ENTRY;

	if (~flags & PROMPT_INCREMENTAL)
		c->tty.flags |= (TTY_NOCURSOR|TTY_FREEZE);
	c->flags |= CLIENT_REDRAWSTATUS;

	if ((flags & PROMPT_INCREMENTAL) && *tmp != '\0') {
		xasprintf(&cp, "=%s", tmp);
		c->prompt_inputcb(c, c->prompt_data, cp, 0);
		free(cp);
	}

	free(tmp);
	format_free(ft);
}