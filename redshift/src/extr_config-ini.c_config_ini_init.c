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
typedef  int /*<<< orphan*/  line ;
struct TYPE_6__ {TYPE_3__* sections; } ;
typedef  TYPE_1__ config_ini_state_t ;
struct TYPE_7__ {int /*<<< orphan*/ * value; int /*<<< orphan*/ * name; struct TYPE_7__* next; } ;
typedef  TYPE_2__ config_ini_setting_t ;
struct TYPE_8__ {TYPE_2__* settings; int /*<<< orphan*/ * name; struct TYPE_8__* next; } ;
typedef  TYPE_3__ config_ini_section_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAX_LINE_LENGTH ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  config_ini_free (TYPE_1__*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/ * open_config_file (char const*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 size_t strcspn (char*,char*) ; 
 int strlen (char*) ; 
 int strspn (char*,char*) ; 

int
config_ini_init(config_ini_state_t *state, const char *filepath)
{
	config_ini_section_t *section = NULL;
	state->sections = NULL;

	FILE *f = open_config_file(filepath);
	if (f == NULL) {
		/* Only a serious error if a file was explicitly requested. */
		if (filepath != NULL) return -1;
		return 0;
	}

	char line[MAX_LINE_LENGTH];
	char *s;

	while (1) {
		/* Handle the file input linewise. */
		char *r = fgets(line, sizeof(line), f);
		if (r == NULL) break;

		/* Strip leading blanks and trailing newline. */
		s = line + strspn(line, " \t");
		s[strcspn(s, "\r\n")] = '\0';

		/* Skip comments and empty lines. */
		if (s[0] == ';' || s[0] == '#' || s[0] == '\0') continue;

		if (s[0] == '[') {
			/* Read name of section. */
			const char *name = s+1;
			char *end = strchr(s, ']');
			if (end == NULL || end[1] != '\0' || end == name) {
				fputs(_("Malformed section header in config"
					" file.\n"), stderr);
				fclose(f);
				config_ini_free(state);
				return -1;
			}

			*end = '\0';

			/* Create section. */
			section = malloc(sizeof(config_ini_section_t));
			if (section == NULL) {
				fclose(f);
				config_ini_free(state);
				return -1;
			}

			/* Insert into section list. */
			section->name = NULL;
			section->settings = NULL;
			section->next = state->sections;
			state->sections = section;

			/* Copy section name. */
			section->name = malloc(end - name + 1);
			if (section->name == NULL) {
				fclose(f);
				config_ini_free(state);
				return -1;
			}

			memcpy(section->name, name, end - name + 1);
		} else {
			/* Split assignment at equals character. */
			char *end = strchr(s, '=');
			if (end == NULL || end == s) {
				fputs(_("Malformed assignment in config"
					" file.\n"), stderr);
				fclose(f);
				config_ini_free(state);
				return -1;
			}

			*end = '\0';
			char *value = end + 1;

			if (section == NULL) {
				fputs(_("Assignment outside section in config"
					" file.\n"), stderr);
				fclose(f);
				config_ini_free(state);
				return -1;
			}

			/* Create section. */
			config_ini_setting_t *setting =
				malloc(sizeof(config_ini_setting_t));
			if (setting == NULL) {
				fclose(f);
				config_ini_free(state);
				return -1;
			}

			/* Insert into section list. */
			setting->name = NULL;
			setting->value = NULL;
			setting->next = section->settings;
			section->settings = setting;

			/* Copy name of setting. */
			setting->name = malloc(end - s + 1);
			if (setting->name == NULL) {
				fclose(f);
				config_ini_free(state);
				return -1;
			}

			memcpy(setting->name, s, end - s + 1);

			/* Copy setting value. */
			size_t value_len = strlen(value) + 1;
			setting->value = malloc(value_len);
			if (setting->value == NULL) {
				fclose(f);
				config_ini_free(state);
				return -1;
			}

			memcpy(setting->value, value, value_len);
		}
	}

	fclose(f);

	return 0;
}