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
typedef  double uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  fd; TYPE_2__* crtcs; } ;
typedef  TYPE_1__ drm_state_t ;
struct TYPE_5__ {scalar_t__ crtc_num; int gamma_size; int /*<<< orphan*/  crtc_id; } ;
typedef  TYPE_2__ drm_crtc_state_t ;
typedef  int /*<<< orphan*/  color_setting_t ;

/* Variables and functions */
 int UINT16_MAX ; 
 int /*<<< orphan*/  colorramp_fill (double*,double*,double*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  drmModeCrtcSetGamma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,double*,double*,double*) ; 
 int /*<<< orphan*/  free (double*) ; 
 double* malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 double* realloc (double*,int) ; 

__attribute__((used)) static int
drm_set_temperature(
	drm_state_t *state, const color_setting_t *setting, int preserve)
{
	drm_crtc_state_t *crtcs = state->crtcs;
	int last_gamma_size = 0;
	uint16_t *r_gamma = NULL;
	uint16_t *g_gamma = NULL;
	uint16_t *b_gamma = NULL;

	for (; crtcs->crtc_num >= 0; crtcs++) {
		if (crtcs->gamma_size <= 1)
			continue;
		if (crtcs->gamma_size != last_gamma_size) {
			if (last_gamma_size == 0) {
				r_gamma = malloc(3 * crtcs->gamma_size * sizeof(uint16_t));
				g_gamma = r_gamma + crtcs->gamma_size;
				b_gamma = g_gamma + crtcs->gamma_size;
			} else if (crtcs->gamma_size > last_gamma_size) {
				r_gamma = realloc(r_gamma, 3 * crtcs->gamma_size * sizeof(uint16_t));
				g_gamma = r_gamma + crtcs->gamma_size;
				b_gamma = g_gamma + crtcs->gamma_size;
			}
			if (r_gamma == NULL) {
				perror(last_gamma_size == 0 ? "malloc" : "realloc");
				return -1;
			}
			last_gamma_size = crtcs->gamma_size;
		}

		/* Initialize gamma ramps to pure state */
		int ramp_size = crtcs->gamma_size;
		for (int i = 0; i < ramp_size; i++) {
			uint16_t value = (double)i/ramp_size * (UINT16_MAX+1);
			r_gamma[i] = value;
			g_gamma[i] = value;
			b_gamma[i] = value;
		}

		colorramp_fill(r_gamma, g_gamma, b_gamma, crtcs->gamma_size,
			       setting);
		drmModeCrtcSetGamma(state->fd, crtcs->crtc_id, crtcs->gamma_size,
				    r_gamma, g_gamma, b_gamma);
	}

	free(r_gamma);

	return 0;
}