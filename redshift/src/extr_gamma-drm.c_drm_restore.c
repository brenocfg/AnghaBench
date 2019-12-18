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
struct TYPE_4__ {int /*<<< orphan*/  fd; TYPE_2__* crtcs; } ;
typedef  TYPE_1__ drm_state_t ;
struct TYPE_5__ {scalar_t__ crtc_num; int /*<<< orphan*/  b_gamma; int /*<<< orphan*/  g_gamma; int /*<<< orphan*/ * r_gamma; int /*<<< orphan*/  gamma_size; int /*<<< orphan*/  crtc_id; } ;
typedef  TYPE_2__ drm_crtc_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  drmModeCrtcSetGamma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
drm_restore(drm_state_t *state)
{
	drm_crtc_state_t *crtcs = state->crtcs;
	while (crtcs->crtc_num >= 0) {
		if (crtcs->r_gamma != NULL) {
			drmModeCrtcSetGamma(state->fd, crtcs->crtc_id, crtcs->gamma_size,
					    crtcs->r_gamma, crtcs->g_gamma, crtcs->b_gamma);
		}
		crtcs++;
	}
}