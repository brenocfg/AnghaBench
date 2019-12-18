#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  usage; int /*<<< orphan*/ * name; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  usage; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int NCOMMAND ; 
 int /*<<< orphan*/  ZFS_TYPE_POOL ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_2__* command_table ; 
 TYPE_1__* current_command ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* get_usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  print_prop_cb ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zprop_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
usage(boolean_t requested)
{
	FILE *fp = requested ? stdout : stderr;

	if (current_command == NULL) {
		int i;

		(void) fprintf(fp, gettext("usage: zpool command args ...\n"));
		(void) fprintf(fp,
		    gettext("where 'command' is one of the following:\n\n"));

		for (i = 0; i < NCOMMAND; i++) {
			if (command_table[i].name == NULL)
				(void) fprintf(fp, "\n");
			else
				(void) fprintf(fp, "%s",
				    get_usage(command_table[i].usage));
		}
	} else {
		(void) fprintf(fp, gettext("usage:\n"));
		(void) fprintf(fp, "%s", get_usage(current_command->usage));
	}

	if (current_command != NULL &&
	    ((strcmp(current_command->name, "set") == 0) ||
	    (strcmp(current_command->name, "get") == 0) ||
	    (strcmp(current_command->name, "list") == 0))) {

		(void) fprintf(fp,
		    gettext("\nthe following properties are supported:\n"));

		(void) fprintf(fp, "\n\t%-19s  %s   %s\n\n",
		    "PROPERTY", "EDIT", "VALUES");

		/* Iterate over all properties */
		(void) zprop_iter(print_prop_cb, fp, B_FALSE, B_TRUE,
		    ZFS_TYPE_POOL);

		(void) fprintf(fp, "\t%-19s   ", "feature@...");
		(void) fprintf(fp, "YES   disabled | enabled | active\n");

		(void) fprintf(fp, gettext("\nThe feature@ properties must be "
		    "appended with a feature name.\nSee zpool-features(5).\n"));
	}

	/*
	 * See comments at end of main().
	 */
	if (getenv("ZFS_ABORT") != NULL) {
		(void) printf("dumping core by request\n");
		abort();
	}

	exit(requested ? 0 : 2);
}