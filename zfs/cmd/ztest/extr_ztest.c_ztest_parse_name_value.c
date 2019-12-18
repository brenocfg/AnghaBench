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
struct TYPE_3__ {int zo_special_vdevs; int zo_verbose; } ;
typedef  TYPE_1__ ztest_shared_opts_t ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int ZTEST_VDEV_CLASS_OFF ; 
 int ZTEST_VDEV_CLASS_ON ; 
 int ZTEST_VDEV_CLASS_RND ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ztest_parse_name_value(const char *input, ztest_shared_opts_t *zo)
{
	char name[32];
	char *value;
	int state = ZTEST_VDEV_CLASS_RND;

	(void) strlcpy(name, input, sizeof (name));

	value = strchr(name, '=');
	if (value == NULL) {
		(void) fprintf(stderr, "missing value in property=value "
		    "'-C' argument (%s)\n", input);
		usage(B_FALSE);
	}
	*(value) = '\0';
	value++;

	if (strcmp(value, "on") == 0) {
		state = ZTEST_VDEV_CLASS_ON;
	} else if (strcmp(value, "off") == 0) {
		state = ZTEST_VDEV_CLASS_OFF;
	} else if (strcmp(value, "random") == 0) {
		state = ZTEST_VDEV_CLASS_RND;
	} else {
		(void) fprintf(stderr, "invalid property value '%s'\n", value);
		usage(B_FALSE);
	}

	if (strcmp(name, "special") == 0) {
		zo->zo_special_vdevs = state;
	} else {
		(void) fprintf(stderr, "invalid property name '%s'\n", name);
		usage(B_FALSE);
	}
	if (zo->zo_verbose >= 3)
		(void) printf("%s vdev state is '%s'\n", name, value);
}