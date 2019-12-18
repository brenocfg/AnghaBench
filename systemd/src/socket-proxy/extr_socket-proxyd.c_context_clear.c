#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  resolve; int /*<<< orphan*/  event; int /*<<< orphan*/  connections; int /*<<< orphan*/  listen; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  connection_free ; 
 int /*<<< orphan*/  sd_event_source_unref ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_resolve_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_free_with_destructor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void context_clear(Context *context) {
        assert(context);

        set_free_with_destructor(context->listen, sd_event_source_unref);
        set_free_with_destructor(context->connections, connection_free);

        sd_event_unref(context->event);
        sd_resolve_unref(context->resolve);
}