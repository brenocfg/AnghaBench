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
struct seat_data {scalar_t__ version; int /*<<< orphan*/ * pointer; } ;

/* Variables and functions */
 scalar_t__ WL_POINTER_RELEASE_SINCE_VERSION ; 
 int /*<<< orphan*/  wl_pointer_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_pointer_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pointer_destroy(struct seat_data *sd)
{
    if (sd->pointer == NULL)
        return;

    if (sd->version >= WL_POINTER_RELEASE_SINCE_VERSION)
        wl_pointer_release(sd->pointer);
    else
        wl_pointer_destroy(sd->pointer);

    sd->pointer = NULL;
}