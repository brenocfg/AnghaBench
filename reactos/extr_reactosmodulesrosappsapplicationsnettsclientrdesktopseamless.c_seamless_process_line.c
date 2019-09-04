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
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_SEAMLESS (char*) ; 
 int /*<<< orphan*/  False ; 
 unsigned long SEAMLESSRDP_HELLO_HIDDEN ; 
 int /*<<< orphan*/  True ; 
 char* seamless_get_token (char**) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 
 void* strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_seamless_ack (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  ui_seamless_begin (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ui_seamless_create_window (int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ui_seamless_destroy_group (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ui_seamless_destroy_window (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ui_seamless_hide_desktop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ui_seamless_move_window (int /*<<< orphan*/ *,unsigned long,int,int,int,int,unsigned long) ; 
 int /*<<< orphan*/  ui_seamless_restack_window (int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ui_seamless_setstate (int /*<<< orphan*/ *,unsigned long,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  ui_seamless_settitle (int /*<<< orphan*/ *,unsigned long,char*,unsigned long) ; 
 int /*<<< orphan*/  ui_seamless_syncbegin (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ui_seamless_unhide_desktop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unimpl (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static BOOL
seamless_process_line(RDPCLIENT * This, const char *line, void *data)
{
	char *p, *l;
	char *tok1, *tok2, *tok3, *tok4, *tok5, *tok6, *tok7, *tok8;
	unsigned long id, flags;
	char *endptr;

	l = xstrdup(line);
	p = l;

	DEBUG_SEAMLESS(("seamlessrdp got:%s\n", p));

	tok1 = seamless_get_token(&p);
	tok2 = seamless_get_token(&p);
	tok3 = seamless_get_token(&p);
	tok4 = seamless_get_token(&p);
	tok5 = seamless_get_token(&p);
	tok6 = seamless_get_token(&p);
	tok7 = seamless_get_token(&p);
	tok8 = seamless_get_token(&p);

	if (!strcmp("CREATE", tok1))
	{
		unsigned long group, parent;
		if (!tok6)
			return False;

		id = strtoul(tok3, &endptr, 0);
		if (*endptr)
			return False;

		group = strtoul(tok4, &endptr, 0);
		if (*endptr)
			return False;

		parent = strtoul(tok5, &endptr, 0);
		if (*endptr)
			return False;

		flags = strtoul(tok6, &endptr, 0);
		if (*endptr)
			return False;

		ui_seamless_create_window(This, id, group, parent, flags);
	}
	else if (!strcmp("DESTROY", tok1))
	{
		if (!tok4)
			return False;

		id = strtoul(tok3, &endptr, 0);
		if (*endptr)
			return False;

		flags = strtoul(tok4, &endptr, 0);
		if (*endptr)
			return False;

		ui_seamless_destroy_window(This, id, flags);

	}
	else if (!strcmp("DESTROYGRP", tok1))
	{
		if (!tok4)
			return False;

		id = strtoul(tok3, &endptr, 0);
		if (*endptr)
			return False;

		flags = strtoul(tok4, &endptr, 0);
		if (*endptr)
			return False;

		ui_seamless_destroy_group(This, id, flags);
	}
	else if (!strcmp("SETICON", tok1))
	{
		unimpl("SeamlessRDP SETICON1\n");
	}
	else if (!strcmp("POSITION", tok1))
	{
		int x, y, width, height;

		if (!tok8)
			return False;

		id = strtoul(tok3, &endptr, 0);
		if (*endptr)
			return False;

		x = strtol(tok4, &endptr, 0);
		if (*endptr)
			return False;
		y = strtol(tok5, &endptr, 0);
		if (*endptr)
			return False;

		width = strtol(tok6, &endptr, 0);
		if (*endptr)
			return False;
		height = strtol(tok7, &endptr, 0);
		if (*endptr)
			return False;

		flags = strtoul(tok8, &endptr, 0);
		if (*endptr)
			return False;

		ui_seamless_move_window(This, id, x, y, width, height, flags);
	}
	else if (!strcmp("ZCHANGE", tok1))
	{
		unsigned long behind;

		id = strtoul(tok3, &endptr, 0);
		if (*endptr)
			return False;

		behind = strtoul(tok4, &endptr, 0);
		if (*endptr)
			return False;

		flags = strtoul(tok5, &endptr, 0);
		if (*endptr)
			return False;

		ui_seamless_restack_window(This, id, behind, flags);
	}
	else if (!strcmp("TITLE", tok1))
	{
		if (!tok5)
			return False;

		id = strtoul(tok3, &endptr, 0);
		if (*endptr)
			return False;

		flags = strtoul(tok5, &endptr, 0);
		if (*endptr)
			return False;

		ui_seamless_settitle(This, id, tok4, flags);
	}
	else if (!strcmp("STATE", tok1))
	{
		unsigned int state;

		if (!tok5)
			return False;

		id = strtoul(tok3, &endptr, 0);
		if (*endptr)
			return False;

		state = strtoul(tok4, &endptr, 0);
		if (*endptr)
			return False;

		flags = strtoul(tok5, &endptr, 0);
		if (*endptr)
			return False;

		ui_seamless_setstate(This, id, state, flags);
	}
	else if (!strcmp("DEBUG", tok1))
	{
		DEBUG_SEAMLESS(("SeamlessRDP:%s\n", line));
	}
	else if (!strcmp("SYNCBEGIN", tok1))
	{
		if (!tok3)
			return False;

		flags = strtoul(tok3, &endptr, 0);
		if (*endptr)
			return False;

		ui_seamless_syncbegin(This, flags);
	}
	else if (!strcmp("SYNCEND", tok1))
	{
		if (!tok3)
			return False;

		flags = strtoul(tok3, &endptr, 0);
		if (*endptr)
			return False;

		/* do nothing, currently */
	}
	else if (!strcmp("HELLO", tok1))
	{
		if (!tok3)
			return False;

		flags = strtoul(tok3, &endptr, 0);
		if (*endptr)
			return False;

		ui_seamless_begin(This, !!(flags & SEAMLESSRDP_HELLO_HIDDEN));
	}
	else if (!strcmp("ACK", tok1))
	{
		unsigned int serial;

		serial = strtoul(tok3, &endptr, 0);
		if (*endptr)
			return False;

		ui_seamless_ack(This, serial);
	}
	else if (!strcmp("HIDE", tok1))
	{
		if (!tok3)
			return False;

		flags = strtoul(tok3, &endptr, 0);
		if (*endptr)
			return False;

		ui_seamless_hide_desktop(This);
	}
	else if (!strcmp("UNHIDE", tok1))
	{
		if (!tok3)
			return False;

		flags = strtoul(tok3, &endptr, 0);
		if (*endptr)
			return False;

		ui_seamless_unhide_desktop(This);
	}


	xfree(l);
	return True;
}