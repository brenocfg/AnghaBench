#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int locked_hint; } ;
typedef  TYPE_1__ Session ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  session_send_changed (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 

void session_set_locked_hint(Session *s, bool b) {
        assert(s);

        if (s->locked_hint == b)
                return;

        s->locked_hint = b;

        session_send_changed(s, "LockedHint", NULL);
}