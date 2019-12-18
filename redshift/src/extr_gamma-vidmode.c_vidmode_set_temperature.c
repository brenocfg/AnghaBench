#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ramp_size; int /*<<< orphan*/  screen_num; int /*<<< orphan*/  display; int /*<<< orphan*/  saved_ramps; } ;
typedef  TYPE_1__ vidmode_state_t ;
typedef  double uint16_t ;
typedef  int /*<<< orphan*/  color_setting_t ;

/* Variables and functions */
 int UINT16_MAX ; 
 int XF86VidModeSetGammaRamp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double*,double*,double*) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  colorramp_fill (double*,double*,double*,double,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (double*) ; 
 double* malloc (int) ; 
 int /*<<< orphan*/  memcpy (double*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
vidmode_set_temperature(
	vidmode_state_t *state, const color_setting_t *setting, int preserve)
{
	int r;

	/* Create new gamma ramps */
	uint16_t *gamma_ramps = malloc(3*state->ramp_size*sizeof(uint16_t));
	if (gamma_ramps == NULL) {
		perror("malloc");
		return -1;
	}

	uint16_t *gamma_r = &gamma_ramps[0*state->ramp_size];
	uint16_t *gamma_g = &gamma_ramps[1*state->ramp_size];
	uint16_t *gamma_b = &gamma_ramps[2*state->ramp_size];

	if (preserve) {
		/* Initialize gamma ramps from saved state */
		memcpy(gamma_ramps, state->saved_ramps,
		       3*state->ramp_size*sizeof(uint16_t));
	} else {
		/* Initialize gamma ramps to pure state */
		for (int i = 0; i < state->ramp_size; i++) {
			uint16_t value = (double)i/state->ramp_size *
				(UINT16_MAX+1);
			gamma_r[i] = value;
			gamma_g[i] = value;
			gamma_b[i] = value;
		}
	}

	colorramp_fill(gamma_r, gamma_g, gamma_b, state->ramp_size,
		       setting);

	/* Set new gamma ramps */
	r = XF86VidModeSetGammaRamp(state->display, state->screen_num,
				    state->ramp_size, gamma_r, gamma_g,
				    gamma_b);
	if (!r) {
		fprintf(stderr, _("X request failed: %s\n"),
			"XF86VidModeSetGammaRamp");
		free(gamma_ramps);
		return -1;
	}

	free(gamma_ramps);

	return 0;
}