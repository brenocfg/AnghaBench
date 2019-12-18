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
struct TYPE_5__ {int idle_hint; int /*<<< orphan*/  manager; int /*<<< orphan*/  user; scalar_t__ seat; int /*<<< orphan*/  idle_hint_timestamp; } ;
typedef  TYPE_1__ Session ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dual_timestamp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  manager_send_changed (int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seat_send_changed (scalar_t__,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_send_changed (TYPE_1__*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_send_changed (int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ *) ; 

void session_set_idle_hint(Session *s, bool b) {
        assert(s);

        if (s->idle_hint == b)
                return;

        s->idle_hint = b;
        dual_timestamp_get(&s->idle_hint_timestamp);

        session_send_changed(s, "IdleHint", "IdleSinceHint", "IdleSinceHintMonotonic", NULL);

        if (s->seat)
                seat_send_changed(s->seat, "IdleHint", "IdleSinceHint", "IdleSinceHintMonotonic", NULL);

        user_send_changed(s->user, "IdleHint", "IdleSinceHint", "IdleSinceHintMonotonic", NULL);
        manager_send_changed(s->manager, "IdleHint", "IdleSinceHint", "IdleSinceHintMonotonic", NULL);
}