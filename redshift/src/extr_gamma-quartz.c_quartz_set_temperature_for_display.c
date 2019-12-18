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
struct TYPE_5__ {TYPE_1__* displays; } ;
typedef  TYPE_2__ quartz_state_t ;
typedef  int /*<<< orphan*/  color_setting_t ;
struct TYPE_4__ {int ramp_size; int /*<<< orphan*/  saved_ramps; int /*<<< orphan*/  display; } ;
typedef  scalar_t__ CGError ;
typedef  int /*<<< orphan*/  CGDirectDisplayID ;

/* Variables and functions */
 scalar_t__ CGSetDisplayTransferByTable (int /*<<< orphan*/ ,int,float*,float*,float*) ; 
 int /*<<< orphan*/  colorramp_fill_float (float*,float*,float*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  free (float*) ; 
 scalar_t__ kCGErrorSuccess ; 
 float* malloc (int) ; 
 int /*<<< orphan*/  memcpy (float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void
quartz_set_temperature_for_display(
	quartz_state_t *state, int display_index,
	const color_setting_t *setting, int preserve)
{
	CGDirectDisplayID display = state->displays[display_index].display;
	uint32_t ramp_size = state->displays[display_index].ramp_size;

	/* Create new gamma ramps */
	float *gamma_ramps = malloc(3*ramp_size*sizeof(float));
	if (gamma_ramps == NULL) {
		perror("malloc");
		return;
	}

	float *gamma_r = &gamma_ramps[0*ramp_size];
	float *gamma_g = &gamma_ramps[1*ramp_size];
	float *gamma_b = &gamma_ramps[2*ramp_size];

	if (preserve) {
		/* Initialize gamma ramps from saved state */
		memcpy(gamma_ramps, state->displays[display_index].saved_ramps,
		       3*ramp_size*sizeof(float));
	} else {
		/* Initialize gamma ramps to pure state */
		for (int i = 0; i < ramp_size; i++) {
			float value = (double)i/ramp_size;
			gamma_r[i] = value;
			gamma_g[i] = value;
			gamma_b[i] = value;
		}
	}

	colorramp_fill_float(gamma_r, gamma_g, gamma_b, ramp_size,
			     setting);

	CGError error =
		CGSetDisplayTransferByTable(display, ramp_size,
					    gamma_r, gamma_g, gamma_b);
	if (error != kCGErrorSuccess) {
		free(gamma_ramps);
		return;
	}

	free(gamma_ramps);
}