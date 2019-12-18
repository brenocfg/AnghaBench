#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ start; } ;
struct TYPE_8__ {scalar_t__ temperature; void** gamma; void* brightness; } ;
struct TYPE_7__ {scalar_t__ temperature; void** gamma; void* brightness; } ;
struct TYPE_9__ {TYPE_5__ dusk; TYPE_5__ dawn; TYPE_2__ night; TYPE_1__ day; void* low; void* high; } ;
struct TYPE_10__ {int use_fade; TYPE_3__ scheme; int /*<<< orphan*/ * provider; int /*<<< orphan*/ * method; } ;
typedef  TYPE_4__ options_t ;
typedef  int /*<<< orphan*/  location_provider_t ;
typedef  int /*<<< orphan*/  gamma_method_t ;

/* Variables and functions */
 char* _ (char*) ; 
 void* atof (char const*) ; 
 void* atoi (char const*) ; 
 int /*<<< orphan*/ * find_gamma_method (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/ * find_location_provider (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ isnan (void*) ; 
 int /*<<< orphan*/  memcpy (void**,void**,int) ; 
 int parse_gamma_string (char const*,void**) ; 
 int parse_transition_range (char const*,TYPE_5__*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static int
parse_config_file_option(
	const char *key, const char *value, options_t *options,
	const gamma_method_t *gamma_methods,
	const location_provider_t *location_providers)
{
	if (strcasecmp(key, "temp-day") == 0) {
		if (options->scheme.day.temperature < 0) {
			options->scheme.day.temperature = atoi(value);
		}
	} else if (strcasecmp(key, "temp-night") == 0) {
		if (options->scheme.night.temperature < 0) {
			options->scheme.night.temperature = atoi(value);
		}
	} else if (strcasecmp(key, "transition") == 0 ||
		   strcasecmp(key, "fade") == 0) {
		/* "fade" is preferred, "transition" is
		   deprecated as the setting key. */
		if (options->use_fade < 0) {
			options->use_fade = !!atoi(value);
		}
	} else if (strcasecmp(key, "brightness") == 0) {
		if (isnan(options->scheme.day.brightness)) {
			options->scheme.day.brightness = atof(value);
		}
		if (isnan(options->scheme.night.brightness)) {
			options->scheme.night.brightness = atof(value);
		}
	} else if (strcasecmp(key, "brightness-day") == 0) {
		if (isnan(options->scheme.day.brightness)) {
			options->scheme.day.brightness = atof(value);
		}
	} else if (strcasecmp(key, "brightness-night") == 0) {
		if (isnan(options->scheme.night.brightness)) {
			options->scheme.night.brightness = atof(value);
		}
	} else if (strcasecmp(key, "elevation-high") == 0) {
		options->scheme.high = atof(value);
	} else if (strcasecmp(key, "elevation-low") == 0) {
		options->scheme.low = atof(value);
	} else if (strcasecmp(key, "gamma") == 0) {
		if (isnan(options->scheme.day.gamma[0])) {
			int r = parse_gamma_string(
				value, options->scheme.day.gamma);
			if (r < 0) {
				fputs(_("Malformed gamma setting.\n"), stderr);
				return -1;
			}
			memcpy(options->scheme.night.gamma,
			       options->scheme.day.gamma,
			       sizeof(options->scheme.night.gamma));
		}
	} else if (strcasecmp(key, "gamma-day") == 0) {
		if (isnan(options->scheme.day.gamma[0])) {
			int r = parse_gamma_string(
				value, options->scheme.day.gamma);
			if (r < 0) {
				fputs(_("Malformed gamma setting.\n"), stderr);
				return -1;
			}
		}
	} else if (strcasecmp(key, "gamma-night") == 0) {
		if (isnan(options->scheme.night.gamma[0])) {
			int r = parse_gamma_string(
				value, options->scheme.night.gamma);
			if (r < 0) {
				fputs(_("Malformed gamma setting.\n"), stderr);
				return -1;
			}
		}
	} else if (strcasecmp(key, "adjustment-method") == 0) {
		if (options->method == NULL) {
			options->method = find_gamma_method(
				gamma_methods, value);
			if (options->method == NULL) {
				fprintf(stderr, _("Unknown adjustment"
						  " method `%s'.\n"), value);
				return -1;
			}
		}
	} else if (strcasecmp(key, "location-provider") == 0) {
		if (options->provider == NULL) {
			options->provider = find_location_provider(
				location_providers, value);
			if (options->provider == NULL) {
				fprintf(stderr, _("Unknown location"
						  " provider `%s'.\n"), value);
				return -1;
			}
		}
	} else if (strcasecmp(key, "dawn-time") == 0) {
		if (options->scheme.dawn.start < 0) {
			int r = parse_transition_range(
				value, &options->scheme.dawn);
			if (r < 0) {
				fprintf(stderr, _("Malformed dawn-time"
						  " setting `%s'.\n"), value);
				return -1;
			}
		}
	} else if (strcasecmp(key, "dusk-time") == 0) {
		if (options->scheme.dusk.start < 0) {
			int r = parse_transition_range(
				value, &options->scheme.dusk);
			if (r < 0) {
				fprintf(stderr, _("Malformed dusk-time"
						  " setting `%s'.\n"), value);
				return -1;
			}
		}
	} else {
		fprintf(stderr, _("Unknown configuration setting `%s'.\n"),
			key);
	}

	return 0;
}