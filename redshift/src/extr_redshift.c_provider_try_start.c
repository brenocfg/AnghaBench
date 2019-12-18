#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  manual_keys ;
typedef  int /*<<< orphan*/  location_state_t ;
struct TYPE_6__ {int (* init ) (int /*<<< orphan*/ **) ;char* name; int (* set_option ) (int /*<<< orphan*/ *,char const*,char*) ;int (* start ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ location_provider_t ;
typedef  int /*<<< orphan*/  config_ini_state_t ;
struct TYPE_7__ {char const* name; char* value; struct TYPE_7__* next; } ;
typedef  TYPE_2__ config_ini_setting_t ;
struct TYPE_8__ {TYPE_2__* settings; } ;
typedef  TYPE_3__ config_ini_section_t ;

/* Variables and functions */
 char* _ (char*) ; 
 TYPE_3__* config_ini_get_section (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int stub1 (int /*<<< orphan*/ **) ; 
 int stub2 (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 int stub4 (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *) ; 
 int stub6 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
provider_try_start(const location_provider_t *provider,
		   location_state_t **state, config_ini_state_t *config,
		   char *args)
{
	int r;

	r = provider->init(state);
	if (r < 0) {
		fprintf(stderr, _("Initialization of %s failed.\n"),
			provider->name);
		return -1;
	}

	/* Set provider options from config file. */
	config_ini_section_t *section =
		config_ini_get_section(config, provider->name);
	if (section != NULL) {
		config_ini_setting_t *setting = section->settings;
		while (setting != NULL) {
			r = provider->set_option(*state, setting->name,
						 setting->value);
			if (r < 0) {
				provider->free(*state);
				fprintf(stderr, _("Failed to set %s"
						  " option.\n"),
					provider->name);
				/* TRANSLATORS: `help' must not be
				   translated. */
				fprintf(stderr, _("Try `-l %s:help' for more"
						  " information.\n"),
					provider->name);
				return -1;
			}
			setting = setting->next;
		}
	}

	/* Set provider options from command line. */
	const char *manual_keys[] = { "lat", "lon" };
	int i = 0;
	while (args != NULL) {
		char *next_arg = strchr(args, ':');
		if (next_arg != NULL) *(next_arg++) = '\0';

		const char *key = args;
		char *value = strchr(args, '=');
		if (value == NULL) {
			/* The options for the "manual" method can be set
			   without keys on the command line for convencience
			   and for backwards compatability. We add the proper
			   keys here before calling set_option(). */
			if (strcmp(provider->name, "manual") == 0 &&
			    i < sizeof(manual_keys)/sizeof(manual_keys[0])) {
				key = manual_keys[i];
				value = args;
			} else {
				fprintf(stderr, _("Failed to parse option `%s'.\n"),
					args);
				return -1;
			}
		} else {
			*(value++) = '\0';
		}

		r = provider->set_option(*state, key, value);
		if (r < 0) {
			provider->free(*state);
			fprintf(stderr, _("Failed to set %s option.\n"),
				provider->name);
			/* TRANSLATORS: `help' must not be translated. */
			fprintf(stderr, _("Try `-l %s:help' for more"
					  " information.\n"), provider->name);
			return -1;
		}

		args = next_arg;
		i += 1;
	}

	/* Start provider. */
	r = provider->start(*state);
	if (r < 0) {
		provider->free(*state);
		fprintf(stderr, _("Failed to start provider %s.\n"),
			provider->name);
		return -1;
	}

	return 0;
}