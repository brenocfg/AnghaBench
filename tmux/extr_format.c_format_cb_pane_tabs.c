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
typedef  scalar_t__ u_int ;
struct TYPE_4__ {int /*<<< orphan*/  tabs; TYPE_1__* grid; } ;
struct window_pane {TYPE_2__ base; } ;
struct format_tree {struct window_pane* wp; } ;
struct format_entry {int /*<<< orphan*/  value; } ;
struct evbuffer {int dummy; } ;
struct TYPE_3__ {scalar_t__ sx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_DATA (struct evbuffer*) ; 
 int EVBUFFER_LENGTH (struct evbuffer*) ; 
 int /*<<< orphan*/  bit_test (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  evbuffer_add (struct evbuffer*,char*,int) ; 
 int /*<<< orphan*/  evbuffer_add_printf (struct evbuffer*,char*,scalar_t__) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 struct evbuffer* evbuffer_new () ; 
 int /*<<< orphan*/  fatalx (char*) ; 
 int /*<<< orphan*/  xasprintf (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
format_cb_pane_tabs(struct format_tree *ft, struct format_entry *fe)
{
	struct window_pane	*wp = ft->wp;
	struct evbuffer		*buffer;
	u_int			 i;
	int			 size;

	if (wp == NULL)
		return;

	buffer = evbuffer_new();
	if (buffer == NULL)
		fatalx("out of memory");
	for (i = 0; i < wp->base.grid->sx; i++) {
		if (!bit_test(wp->base.tabs, i))
			continue;

		if (EVBUFFER_LENGTH(buffer) > 0)
			evbuffer_add(buffer, ",", 1);
		evbuffer_add_printf(buffer, "%u", i);
	}
	if ((size = EVBUFFER_LENGTH(buffer)) != 0)
		xasprintf(&fe->value, "%.*s", size, EVBUFFER_DATA(buffer));
	evbuffer_free(buffer);
}