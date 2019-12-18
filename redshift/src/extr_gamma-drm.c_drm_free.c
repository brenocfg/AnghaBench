#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int crtc_num; int fd; int /*<<< orphan*/ * res; struct TYPE_5__* crtcs; struct TYPE_5__* r_gamma; } ;
typedef  TYPE_1__ drm_state_t ;
typedef  TYPE_1__ drm_crtc_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  drmModeFreeResources (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
drm_free(drm_state_t *state)
{
	if (state->crtcs != NULL) {
		drm_crtc_state_t *crtcs = state->crtcs;
		while (crtcs->crtc_num >= 0) {
			free(crtcs->r_gamma);
			crtcs->crtc_num = -1;
			crtcs++;
		}
		free(state->crtcs);
		state->crtcs = NULL;
	}
	if (state->res != NULL) {
		drmModeFreeResources(state->res);
		state->res = NULL;
	}
	if (state->fd >= 0) {
		close(state->fd);
		state->fd = -1;
	}

	free(state);
}