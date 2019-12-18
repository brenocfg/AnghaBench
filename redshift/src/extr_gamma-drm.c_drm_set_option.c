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
struct TYPE_3__ {scalar_t__ crtc_num; void* card_num; } ;
typedef  TYPE_1__ drm_state_t ;

/* Variables and functions */
 char* _ (char*) ; 
 void* atoi (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static int
drm_set_option(drm_state_t *state, const char *key, const char *value)
{
	if (strcasecmp(key, "card") == 0) {
		state->card_num = atoi(value);
	} else if (strcasecmp(key, "crtc") == 0) {
		state->crtc_num = atoi(value);
		if (state->crtc_num < 0) {
			fprintf(stderr, _("CRTC must be a non-negative integer\n"));
			return -1;
		}
	} else {
		fprintf(stderr, _("Unknown method parameter: `%s'.\n"), key);
		return -1;
	}

	return 0;
}