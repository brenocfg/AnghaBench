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
struct seat_data {int /*<<< orphan*/  cursor_deadline; int /*<<< orphan*/  owner; int /*<<< orphan*/  cursor_timeout; int /*<<< orphan*/ * pointer; int /*<<< orphan*/  seat; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT64_MAX ; 
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pointer_cbs ; 
 int /*<<< orphan*/  var_InheritInteger (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl_pointer_add_listener (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct seat_data*) ; 
 int /*<<< orphan*/ * wl_seat_get_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pointer_create(struct seat_data *sd)
{
    if (sd->pointer != NULL)
        return;

    sd->pointer = wl_seat_get_pointer(sd->seat);
    if (likely(sd->pointer != NULL))
        wl_pointer_add_listener(sd->pointer, &pointer_cbs, sd);

    sd->cursor_timeout = VLC_TICK_FROM_MS( var_InheritInteger(sd->owner, "mouse-hide-timeout") );
    sd->cursor_deadline = INT64_MAX;
}