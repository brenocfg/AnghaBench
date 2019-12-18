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
struct TYPE_4__ {int crtc_count; int /*<<< orphan*/  conn; struct TYPE_4__* crtc_num; struct TYPE_4__* crtcs; struct TYPE_4__* saved_ramps; } ;
typedef  TYPE_1__ randr_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  xcb_disconnect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
randr_free(randr_state_t *state)
{
	/* Free CRTC state */
	for (int i = 0; i < state->crtc_count; i++) {
		free(state->crtcs[i].saved_ramps);
	}
	free(state->crtcs);
	free(state->crtc_num);

	/* Close connection */
	xcb_disconnect(state->conn);

	free(state);
}