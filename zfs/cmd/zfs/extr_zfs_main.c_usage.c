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
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int NCOMMAND ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_2__* command_table ; 
 TYPE_1__* current_command ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* get_usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usage_prop_cb ; 
 int /*<<< orphan*/  zprop_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usage(boolean_t requested)
{
	int i;
	boolean_t show_properties = B_FALSE;
	FILE *fp = requested ? stdout : stderr;

	if (current_command == NULL) {

		(void) fprintf(fp, gettext("usage: zfs command args ...\n"));
		(void) fprintf(fp,
		    gettext("where 'command' is one of the following:\n\n"));

		for (i = 0; i < NCOMMAND; i++) {
			if (command_table[i].name == NULL)
				(void) fprintf(fp, "\n");
			else
				(void) fprintf(fp, "%s",
				    get_usage(command_table[i].usage));
		}

		(void) fprintf(fp, gettext("\nEach dataset is of the form: "
		    "pool/[dataset/]*dataset[@name]\n"));
	} else {
		(void) fprintf(fp, gettext("usage:\n"));
		(void) fprintf(fp, "%s", get_usage(current_command->usage));
	}

	if (current_command != NULL &&
	    (strcmp(current_command->name, "set") == 0 ||
	    strcmp(current_command->name, "get") == 0 ||
	    strcmp(current_command->name, "inherit") == 0 ||
	    strcmp(current_command->name, "list") == 0))
		show_properties = B_TRUE;

	if (show_properties) {
		(void) fprintf(fp,
		    gettext("\nThe following properties are supported:\n"));

		(void) fprintf(fp, "\n\t%-14s %s  %s   %s\n\n",
		    "PROPERTY", "EDIT", "INHERIT", "VALUES");

		/* Iterate over all properties */
		(void) zprop_iter(usage_prop_cb, fp, B_FALSE, B_TRUE,
		    ZFS_TYPE_DATASET);

		(void) fprintf(fp, "\t%-15s ", "userused@...");
		(void) fprintf(fp, " NO       NO   <size>\n");
		(void) fprintf(fp, "\t%-15s ", "groupused@...");
		(void) fprintf(fp, " NO       NO   <size>\n");
		(void) fprintf(fp, "\t%-15s ", "projectused@...");
		(void) fprintf(fp, " NO       NO   <size>\n");
		(void) fprintf(fp, "\t%-15s ", "userobjused@...");
		(void) fprintf(fp, " NO       NO   <size>\n");
		(void) fprintf(fp, "\t%-15s ", "groupobjused@...");
		(void) fprintf(fp, " NO       NO   <size>\n");
		(void) fprintf(fp, "\t%-15s ", "projectobjused@...");
		(void) fprintf(fp, " NO       NO   <size>\n");
		(void) fprintf(fp, "\t%-15s ", "userquota@...");
		(void) fprintf(fp, "YES       NO   <size> | none\n");
		(void) fprintf(fp, "\t%-15s ", "groupquota@...");
		(void) fprintf(fp, "YES       NO   <size> | none\n");
		(void) fprintf(fp, "\t%-15s ", "projectquota@...");
		(void) fprintf(fp, "YES       NO   <size> | none\n");
		(void) fprintf(fp, "\t%-15s ", "userobjquota@...");
		(void) fprintf(fp, "YES       NO   <size> | none\n");
		(void) fprintf(fp, "\t%-15s ", "groupobjquota@...");
		(void) fprintf(fp, "YES       NO   <size> | none\n");
		(void) fprintf(fp, "\t%-15s ", "projectobjquota@...");
		(void) fprintf(fp, "YES       NO   <size> | none\n");
		(void) fprintf(fp, "\t%-15s ", "written@<snap>");
		(void) fprintf(fp, " NO       NO   <size>\n");
		(void) fprintf(fp, "\t%-15s ", "written#<bookmark>");
		(void) fprintf(fp, " NO       NO   <size>\n");

		(void) fprintf(fp, gettext("\nSizes are specified in bytes "
		    "with standard units such as K, M, G, etc.\n"));
		(void) fprintf(fp, gettext("\nUser-defined properties can "
		    "be specified by using a name containing a colon (:).\n"));
		(void) fprintf(fp, gettext("\nThe {user|group|project}"
		    "[obj]{used|quota}@ properties must be appended with\n"
		    "a user|group|project specifier of one of these forms:\n"
		    "    POSIX name      (eg: \"matt\")\n"
		    "    POSIX id        (eg: \"126829\")\n"
		    "    SMB name@domain (eg: \"matt@sun\")\n"
		    "    SMB SID         (eg: \"S-1-234-567-89\")\n"));
	} else {
		(void) fprintf(fp,
		    gettext("\nFor the property list, run: %s\n"),
		    "zfs set|get");
		(void) fprintf(fp,
		    gettext("\nFor the delegated permission list, run: %s\n"),
		    "zfs allow|unallow");
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