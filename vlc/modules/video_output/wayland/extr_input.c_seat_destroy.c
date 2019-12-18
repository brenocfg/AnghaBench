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
struct seat_data {scalar_t__ version; int /*<<< orphan*/  seat; int /*<<< orphan*/ * xkb; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 scalar_t__ WL_SEAT_RELEASE_SINCE_VERSION ; 
 int /*<<< orphan*/  free (struct seat_data*) ; 
 int /*<<< orphan*/  keyboard_destroy (struct seat_data*) ; 
 int /*<<< orphan*/  pointer_destroy (struct seat_data*) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_seat_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_seat_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xkb_context_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void seat_destroy(struct seat_data *sd)
{
    wl_list_remove(&sd->node);

#ifdef HAVE_XKBCOMMON
    keyboard_destroy(sd);

    if (sd->xkb != NULL)
        xkb_context_unref(sd->xkb);
#endif
    pointer_destroy(sd);

    if (sd->version >= WL_SEAT_RELEASE_SINCE_VERSION)
        wl_seat_release(sd->seat);
    else
        wl_seat_destroy(sd->seat);
    free(sd);
}