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
typedef  TYPE_1__* sa_share_impl_t ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  sharepath; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_available () ; 
 int /*<<< orphan*/  nfs_exportfs_temp_fd ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static boolean_t
nfs_is_share_active(sa_share_impl_t impl_share)
{
	int fd;
	char line[512];
	char *tab, *cur;
	FILE *nfs_exportfs_temp_fp;

	if (!nfs_available())
		return (B_FALSE);

	if ((fd = dup(nfs_exportfs_temp_fd)) == -1)
		return (B_FALSE);

	nfs_exportfs_temp_fp = fdopen(fd, "r");

	if (nfs_exportfs_temp_fp == NULL)
		return (B_FALSE);

	if (fseek(nfs_exportfs_temp_fp, 0, SEEK_SET) < 0) {
		fclose(nfs_exportfs_temp_fp);
		return (B_FALSE);
	}

	while (fgets(line, sizeof (line), nfs_exportfs_temp_fp) != NULL) {
		/*
		 * exportfs uses separate lines for the share path
		 * and the export options when the share path is longer
		 * than a certain amount of characters; this ignores
		 * the option lines
		 */
		if (line[0] == '\t')
			continue;

		tab = strchr(line, '\t');

		if (tab != NULL) {
			*tab = '\0';
			cur = tab - 1;
		} else {
			/*
			 * there's no tab character, which means the
			 * NFS options are on a separate line; we just
			 * need to remove the new-line character
			 * at the end of the line
			 */
			cur = line + strlen(line) - 1;
		}

		/* remove trailing spaces and new-line characters */
		while (cur >= line && (*cur == ' ' || *cur == '\n'))
			*cur-- = '\0';

		if (strcmp(line, impl_share->sharepath) == 0) {
			fclose(nfs_exportfs_temp_fp);
			return (B_TRUE);
		}
	}

	fclose(nfs_exportfs_temp_fp);

	return (B_FALSE);
}