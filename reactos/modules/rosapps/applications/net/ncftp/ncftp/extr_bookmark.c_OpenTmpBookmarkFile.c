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
typedef  int /*<<< orphan*/  pathName ;
typedef  int /*<<< orphan*/  path2 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FOPEN_WRITE_TEXT ; 
 int /*<<< orphan*/  OurDirectoryPath (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRNCAT (char*,char*) ; 
 int /*<<< orphan*/  _chmod (char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* gOurDirectoryPath ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  kBookmarkFileName ; 
 int kBookmarkVersion ; 
 int /*<<< orphan*/  kTmpBookmarkFileName ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 

FILE *
OpenTmpBookmarkFile(int nb)
{
	FILE *outfp;
	char pidStr[32];
	char pathName[256], path2[256];

	if (gOurDirectoryPath[0] == '\0')
		return (NULL);		/* Don't create in root directory. */

	(void) OurDirectoryPath(path2, sizeof(path2), kBookmarkFileName);
	(void) OurDirectoryPath(pathName, sizeof(pathName), kTmpBookmarkFileName);
	(void) sprintf(pidStr, "-%u.txt", (unsigned int) getpid());
	(void) STRNCAT(pathName, pidStr);

	outfp = fopen(pathName, FOPEN_WRITE_TEXT);
	if (outfp == NULL) {
		(void) fprintf(stderr, "Could not save bookmark.\n");
		perror(pathName);
		return (NULL);
	}
	(void) _chmod(pathName, 00600);
	if (nb > 0) {
		if (fprintf(outfp, "NcFTP bookmark-file version: %d\nNumber of bookmarks: %d\n", kBookmarkVersion, nb) < 0) {
			(void) fprintf(stderr, "Could not save bookmark.\n");
			perror(pathName);
			(void) fclose(outfp);
			return (NULL);
		}
	} else {
		if (fprintf(outfp, "NcFTP bookmark-file version: %d\nNumber of bookmarks: ??\n", kBookmarkVersion) < 0) {
			(void) fprintf(stderr, "Could not save bookmark.\n");
			perror(pathName);
			(void) fclose(outfp);
			return (NULL);
		}
	}

	return (outfp);
}