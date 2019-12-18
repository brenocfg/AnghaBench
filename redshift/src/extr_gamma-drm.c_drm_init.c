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
struct TYPE_4__ {int crtc_num; int fd; int /*<<< orphan*/ * crtcs; int /*<<< orphan*/ * res; scalar_t__ card_num; } ;
typedef  TYPE_1__ drm_state_t ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static int
drm_init(drm_state_t **state)
{
	/* Initialize state. */
	*state = malloc(sizeof(drm_state_t));
	if (*state == NULL) return -1;

	drm_state_t *s = *state;
	s->card_num = 0;
	s->crtc_num = -1;
	s->fd = -1;
	s->res = NULL;
	s->crtcs = NULL;

	return 0;
}