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
struct TYPE_4__ {float lat; float lon; } ;
struct TYPE_5__ {TYPE_1__ loc; } ;
typedef  TYPE_2__ location_manual_state_t ;

/* Variables and functions */
 char* _ (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 float strtof (char const*,char**) ; 

__attribute__((used)) static int
location_manual_set_option(location_manual_state_t *state, const char *key,
			   const char *value)
{
	/* Parse float value */
	char *end;
	errno = 0;
	float v = strtof(value, &end);
	if (errno != 0 || *end != '\0') {
		fputs(_("Malformed argument.\n"), stderr);
		return -1;
	}

	if (strcasecmp(key, "lat") == 0) {
		state->loc.lat = v;
	} else if (strcasecmp(key, "lon") == 0) {
		state->loc.lon = v;
	} else {
		fprintf(stderr, _("Unknown method parameter: `%s'.\n"), key);
		return -1;
	}

	return 0;
}