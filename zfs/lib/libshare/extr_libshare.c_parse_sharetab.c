#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sa_handle_impl_t ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  ZFS_SHARETAB ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  process_share (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
parse_sharetab(sa_handle_impl_t impl_handle)
{
	FILE *fp;
	char line[512];
	char *eol, *pathname, *resource, *fstype, *options, *description;

	fp = fopen(ZFS_SHARETAB, "r");

	if (fp == NULL)
		return;

	while (fgets(line, sizeof (line), fp) != NULL) {
		eol = line + strlen(line) - 1;

		while (eol >= line) {
			if (*eol != '\r' && *eol != '\n')
				break;

			*eol = '\0';
			eol--;
		}

		pathname = line;

		if ((resource = strchr(pathname, '\t')) == NULL)
			continue;

		*resource = '\0';
		resource++;

		if ((fstype = strchr(resource, '\t')) == NULL)
			continue;

		*fstype = '\0';
		fstype++;

		if ((options = strchr(fstype, '\t')) == NULL)
			continue;

		*options = '\0';
		options++;

		if ((description = strchr(fstype, '\t')) != NULL) {
			*description = '\0';
			description++;
		}

		if (strcmp(resource, "-") == 0)
			resource = NULL;

		(void) process_share(impl_handle, NULL, pathname, resource,
		    fstype, options, description, NULL, B_TRUE);
	}

	fclose(fp);
}