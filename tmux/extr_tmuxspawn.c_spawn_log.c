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
struct winlink {int /*<<< orphan*/  idx; } ;
struct window_pane {int /*<<< orphan*/  id; } ;
struct spawn_context {char* name; int /*<<< orphan*/  idx; int /*<<< orphan*/  flags; TYPE_1__* item; struct window_pane* wp0; struct winlink* wl; struct session* s; } ;
struct session {int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_debug (char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,...) ; 

__attribute__((used)) static void
spawn_log(const char *from, struct spawn_context *sc)
{
	struct session		*s = sc->s;
	struct winlink		*wl = sc->wl;
	struct window_pane	*wp0 = sc->wp0;
	char			 tmp[128];
	const char		*name;

	log_debug("%s: %s, flags=%#x", from, sc->item->name, sc->flags);

	if (wl != NULL && wp0 != NULL)
		xsnprintf(tmp, sizeof tmp, "wl=%d wp0=%%%u", wl->idx, wp0->id);
	else if (wl != NULL)
		xsnprintf(tmp, sizeof tmp, "wl=%d wp0=none", wl->idx);
	else if (wp0 != NULL)
		xsnprintf(tmp, sizeof tmp, "wl=none wp0=%%%u", wp0->id);
	else
		xsnprintf(tmp, sizeof tmp, "wl=none wp0=none");
	log_debug("%s: s=$%u %s idx=%d", from, s->id, tmp, sc->idx);

	name = sc->name;
	if (name == NULL)
		name = "none";
	log_debug("%s: name=%s", from, name);
}