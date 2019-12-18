#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_22__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_setup_t ;
struct TYPE_25__ {scalar_t__ rem; TYPE_1__* data; } ;
typedef  TYPE_2__ xcb_screen_iterator_t ;
struct TYPE_26__ {int num_crtcs; unsigned int size; } ;
typedef  TYPE_3__ xcb_randr_get_screen_resources_current_reply_t ;
typedef  int /*<<< orphan*/  xcb_randr_get_screen_resources_current_cookie_t ;
typedef  TYPE_3__ xcb_randr_get_crtc_gamma_size_reply_t ;
typedef  int /*<<< orphan*/  xcb_randr_get_crtc_gamma_size_cookie_t ;
typedef  TYPE_3__ xcb_randr_get_crtc_gamma_reply_t ;
typedef  int /*<<< orphan*/  xcb_randr_get_crtc_gamma_cookie_t ;
typedef  int /*<<< orphan*/  xcb_randr_crtc_t ;
struct TYPE_27__ {int error_code; } ;
typedef  TYPE_6__ xcb_generic_error_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_28__ {int screen_num; int preferred_screen; int crtc_count; TYPE_22__* crtcs; int /*<<< orphan*/  conn; TYPE_1__* screen; } ;
typedef  TYPE_7__ randr_state_t ;
typedef  int /*<<< orphan*/  randr_crtc_state_t ;
struct TYPE_24__ {unsigned int ramp_size; int /*<<< orphan*/ * saved_ramps; int /*<<< orphan*/  crtc; } ;
struct TYPE_23__ {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 char* _ (char*) ; 
 TYPE_22__* calloc (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * xcb_get_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_randr_get_crtc_gamma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xcb_randr_get_crtc_gamma_blue (TYPE_3__*) ; 
 int /*<<< orphan*/ * xcb_randr_get_crtc_gamma_green (TYPE_3__*) ; 
 int /*<<< orphan*/ * xcb_randr_get_crtc_gamma_red (TYPE_3__*) ; 
 TYPE_3__* xcb_randr_get_crtc_gamma_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__**) ; 
 int /*<<< orphan*/  xcb_randr_get_crtc_gamma_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* xcb_randr_get_crtc_gamma_size_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__**) ; 
 int /*<<< orphan*/  xcb_randr_get_screen_resources_current (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xcb_randr_get_screen_resources_current_crtcs (TYPE_3__*) ; 
 TYPE_3__* xcb_randr_get_screen_resources_current_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__**) ; 
 int /*<<< orphan*/  xcb_screen_next (TYPE_2__*) ; 
 TYPE_2__ xcb_setup_roots_iterator (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
randr_start(randr_state_t *state)
{
	xcb_generic_error_t *error;

	int screen_num = state->screen_num;
	if (screen_num < 0) screen_num = state->preferred_screen;

	/* Get screen */
	const xcb_setup_t *setup = xcb_get_setup(state->conn);
	xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
	state->screen = NULL;

	for (int i = 0; iter.rem > 0; i++) {
		if (i == screen_num) {
			state->screen = iter.data;
			break;
		}
		xcb_screen_next(&iter);
	}

	if (state->screen == NULL) {
		fprintf(stderr, _("Screen %i could not be found.\n"),
			screen_num);
		return -1;
	}

	/* Get list of CRTCs for the screen */
	xcb_randr_get_screen_resources_current_cookie_t res_cookie =
		xcb_randr_get_screen_resources_current(state->conn,
						       state->screen->root);
	xcb_randr_get_screen_resources_current_reply_t *res_reply =
		xcb_randr_get_screen_resources_current_reply(state->conn,
							     res_cookie,
							     &error);

	if (error) {
		fprintf(stderr, _("`%s' returned error %d\n"),
			"RANDR Get Screen Resources Current",
			error->error_code);
		return -1;
	}

	state->crtc_count = res_reply->num_crtcs;
	state->crtcs = calloc(state->crtc_count, sizeof(randr_crtc_state_t));
	if (state->crtcs == NULL) {
		perror("malloc");
		state->crtc_count = 0;
		return -1;
	}

	xcb_randr_crtc_t *crtcs =
		xcb_randr_get_screen_resources_current_crtcs(res_reply);

	/* Save CRTC identifier in state */
	for (int i = 0; i < state->crtc_count; i++) {
		state->crtcs[i].crtc = crtcs[i];
	}

	free(res_reply);

	/* Save size and gamma ramps of all CRTCs.
	   Current gamma ramps are saved so we can restore them
	   at program exit. */
	for (int i = 0; i < state->crtc_count; i++) {
		xcb_randr_crtc_t crtc = state->crtcs[i].crtc;

		/* Request size of gamma ramps */
		xcb_randr_get_crtc_gamma_size_cookie_t gamma_size_cookie =
			xcb_randr_get_crtc_gamma_size(state->conn, crtc);
		xcb_randr_get_crtc_gamma_size_reply_t *gamma_size_reply =
			xcb_randr_get_crtc_gamma_size_reply(state->conn,
							    gamma_size_cookie,
							    &error);

		if (error) {
			fprintf(stderr, _("`%s' returned error %d\n"),
				"RANDR Get CRTC Gamma Size",
				error->error_code);
			return -1;
		}

		unsigned int ramp_size = gamma_size_reply->size;
		state->crtcs[i].ramp_size = ramp_size;

		free(gamma_size_reply);

		if (ramp_size == 0) {
			fprintf(stderr, _("Gamma ramp size too small: %i\n"),
				ramp_size);
			return -1;
		}

		/* Request current gamma ramps */
		xcb_randr_get_crtc_gamma_cookie_t gamma_get_cookie =
			xcb_randr_get_crtc_gamma(state->conn, crtc);
		xcb_randr_get_crtc_gamma_reply_t *gamma_get_reply =
			xcb_randr_get_crtc_gamma_reply(state->conn,
						       gamma_get_cookie,
						       &error);

		if (error) {
			fprintf(stderr, _("`%s' returned error %d\n"),
				"RANDR Get CRTC Gamma", error->error_code);
			return -1;
		}

		uint16_t *gamma_r =
			xcb_randr_get_crtc_gamma_red(gamma_get_reply);
		uint16_t *gamma_g =
			xcb_randr_get_crtc_gamma_green(gamma_get_reply);
		uint16_t *gamma_b =
			xcb_randr_get_crtc_gamma_blue(gamma_get_reply);

		/* Allocate space for saved gamma ramps */
		state->crtcs[i].saved_ramps =
			malloc(3*ramp_size*sizeof(uint16_t));
		if (state->crtcs[i].saved_ramps == NULL) {
			perror("malloc");
			free(gamma_get_reply);
			return -1;
		}

		/* Copy gamma ramps into CRTC state */
		memcpy(&state->crtcs[i].saved_ramps[0*ramp_size], gamma_r,
		       ramp_size*sizeof(uint16_t));
		memcpy(&state->crtcs[i].saved_ramps[1*ramp_size], gamma_g,
		       ramp_size*sizeof(uint16_t));
		memcpy(&state->crtcs[i].saved_ramps[2*ramp_size], gamma_b,
		       ramp_size*sizeof(uint16_t));

		free(gamma_get_reply);
	}

	return 0;
}