#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int display_count; TYPE_1__* displays; } ;
typedef  TYPE_2__ quartz_state_t ;
typedef  int /*<<< orphan*/  quartz_display_state_t ;
struct TYPE_4__ {float* saved_ramps; int ramp_size; int /*<<< orphan*/  display; } ;
typedef  scalar_t__ CGError ;
typedef  int /*<<< orphan*/  CGDirectDisplayID ;

/* Variables and functions */
 int CGDisplayGammaTableCapacity (int /*<<< orphan*/ ) ; 
 scalar_t__ CGGetDisplayTransferByTable (int /*<<< orphan*/ ,int,float*,float*,float*,int*) ; 
 scalar_t__ CGGetOnlineDisplayList (int,int /*<<< orphan*/ *,int*) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ kCGErrorSuccess ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
quartz_start(quartz_state_t *state)
{
	CGError error;
	uint32_t display_count;

	/* Get display count */
	error = CGGetOnlineDisplayList(0, NULL, &display_count);
	if (error != kCGErrorSuccess) return -1;

	state->display_count = display_count;

	CGDirectDisplayID* displays =
		malloc(sizeof(CGDirectDisplayID)*display_count);
	if (displays == NULL) {
		perror("malloc");
		return -1;
	}

	/* Get list of displays */
	error = CGGetOnlineDisplayList(display_count, displays,
				       &display_count);
	if (error != kCGErrorSuccess) {
		free(displays);
		return -1;
	}

	/* Allocate list of display state */
	state->displays = malloc(display_count *
				 sizeof(quartz_display_state_t));
	if (state->displays == NULL) {
		perror("malloc");
		free(displays);
		return -1;
	}

	/* Copy display indentifiers to display state */
	for (int i = 0; i < display_count; i++) {
		state->displays[i].display = displays[i];
		state->displays[i].saved_ramps = NULL;
	}

	free(displays);

	/* Save gamma ramps for all displays in display state */
	for (int i = 0; i < display_count; i++) {
		CGDirectDisplayID display = state->displays[i].display;

		uint32_t ramp_size = CGDisplayGammaTableCapacity(display);
		if (ramp_size == 0) {
			fprintf(stderr, _("Gamma ramp size too small: %i\n"),
				ramp_size);
			return -1;
		}

		state->displays[i].ramp_size = ramp_size;

		/* Allocate space for saved ramps */
		state->displays[i].saved_ramps =
			malloc(3 * ramp_size * sizeof(float));
		if (state->displays[i].saved_ramps == NULL) {
			perror("malloc");
			return -1;
		}

		float *gamma_r = &state->displays[i].saved_ramps[0*ramp_size];
		float *gamma_g = &state->displays[i].saved_ramps[1*ramp_size];
		float *gamma_b = &state->displays[i].saved_ramps[2*ramp_size];

		/* Copy the ramps to allocated space */
		uint32_t sample_count;
		error = CGGetDisplayTransferByTable(display, ramp_size,
						    gamma_r, gamma_g, gamma_b,
						    &sample_count);
		if (error != kCGErrorSuccess ||
		    sample_count != ramp_size) {
			fputs(_("Unable to save current gamma ramp.\n"),
			      stderr);
			return -1;
		}
	}

	return 0;
}