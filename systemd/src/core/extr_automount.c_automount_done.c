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
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_5__ {int /*<<< orphan*/  expire_event_source; void* expire_tokens; void* tokens; int /*<<< orphan*/  where; } ;
typedef  TYPE_1__ Automount ;

/* Variables and functions */
 TYPE_1__* AUTOMOUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  mfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 void* set_free (void*) ; 
 int /*<<< orphan*/  unmount_autofs (TYPE_1__*) ; 

__attribute__((used)) static void automount_done(Unit *u) {
        Automount *a = AUTOMOUNT(u);

        assert(a);

        unmount_autofs(a);

        a->where = mfree(a->where);

        a->tokens = set_free(a->tokens);
        a->expire_tokens = set_free(a->expire_tokens);

        a->expire_event_source = sd_event_source_unref(a->expire_event_source);
}