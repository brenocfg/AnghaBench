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
struct wait_channel {int /*<<< orphan*/  name; int /*<<< orphan*/  lockers; int /*<<< orphan*/  waiters; scalar_t__ woken; scalar_t__ locked; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct wait_channel*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_channels ; 
 struct wait_channel* xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static struct wait_channel *
cmd_wait_for_add(const char *name)
{
	struct wait_channel *wc;

	wc = xmalloc(sizeof *wc);
	wc->name = xstrdup(name);

	wc->locked = 0;
	wc->woken = 0;

	TAILQ_INIT(&wc->waiters);
	TAILQ_INIT(&wc->lockers);

	RB_INSERT(wait_channels, &wait_channels, wc);

	log_debug("add wait channel %s", wc->name);

	return (wc);
}