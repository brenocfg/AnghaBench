#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_void_cookie_t ;
typedef  int /*<<< orphan*/  xcb_randr_crtc_t ;
struct TYPE_7__ {int error_code; } ;
typedef  TYPE_2__ xcb_generic_error_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_8__ {int crtc_count; int /*<<< orphan*/  conn; TYPE_1__* crtcs; } ;
typedef  TYPE_3__ randr_state_t ;
struct TYPE_6__ {unsigned int ramp_size; int /*<<< orphan*/ * saved_ramps; int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  xcb_randr_set_crtc_gamma_checked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* xcb_request_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
randr_restore(randr_state_t *state)
{
	xcb_generic_error_t *error;

	/* Restore CRTC gamma ramps */
	for (int i = 0; i < state->crtc_count; i++) {
		xcb_randr_crtc_t crtc = state->crtcs[i].crtc;

		unsigned int ramp_size = state->crtcs[i].ramp_size;
		uint16_t *gamma_r = &state->crtcs[i].saved_ramps[0*ramp_size];
		uint16_t *gamma_g = &state->crtcs[i].saved_ramps[1*ramp_size];
		uint16_t *gamma_b = &state->crtcs[i].saved_ramps[2*ramp_size];

		/* Set gamma ramps */
		xcb_void_cookie_t gamma_set_cookie =
			xcb_randr_set_crtc_gamma_checked(state->conn, crtc,
							 ramp_size, gamma_r,
							 gamma_g, gamma_b);
		error = xcb_request_check(state->conn, gamma_set_cookie);

		if (error) {
			fprintf(stderr, _("`%s' returned error %d\n"),
				"RANDR Set CRTC Gamma", error->error_code);
			fprintf(stderr, _("Unable to restore CRTC %i\n"), i);
		}
	}
}