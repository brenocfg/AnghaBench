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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  Bookmark ;

/* Variables and functions */
 int /*<<< orphan*/  CloseBookmarkFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FGets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FOPEN_READ_TEXT ; 
 scalar_t__ GetNextBookmark (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OurDirectoryPath (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRNCAT (char*,char*) ; 
 int /*<<< orphan*/  STRNCPY (char*,char*) ; 
 int /*<<< orphan*/  _chmod (char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* gOurDirectoryPath ; 
 int /*<<< orphan*/  kBookmarkFileName ; 
 int kBookmarkMinVersion ; 
 int /*<<< orphan*/  kOldBookmarkFileName ; 
 scalar_t__ rename (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  stderr ; 

FILE *
OpenBookmarkFile(int *numBookmarks0)
{
	char pathName[256], path2[256];
	char line[256];
	FILE *fp;
	int version;
	int numBookmarks;
	Bookmark junkbm;

	if (gOurDirectoryPath[0] == '\0')
		return NULL;		/* Don't create in root directory. */
	(void) OurDirectoryPath(pathName, sizeof(pathName), kBookmarkFileName);
	fp = fopen(pathName, FOPEN_READ_TEXT);
	if (fp == NULL) {
		/* See if it exists under the old name. */
		(void) OurDirectoryPath(path2, sizeof(path2), kOldBookmarkFileName);
		if (rename(path2, pathName) == 0) {
			/* Rename succeeded, now open it. */
			fp = fopen(pathName, FOPEN_READ_TEXT);
			if (fp == NULL)
				return NULL;
		}
		return NULL;		/* Okay to not have one yet. */
	}

	(void) _chmod(pathName, 00600);
	if (FGets(line, sizeof(line), fp) == NULL) {
		(void) fprintf(stderr, "%s: invalid format.\n", pathName);
		(void) fclose(fp);
		return NULL;
	}

	/* Sample line we're looking for:
	 * "NcFTP bookmark-file version: 8"
	 */
	version = -1;
	(void) sscanf(line, "%*s %*s %*s %d", &version);
	if (version < kBookmarkMinVersion) {
		if (version < 0) {
			(void) fprintf(stderr, "%s: invalid format, or bad version.\n", pathName);
			(void) fclose(fp);
			return NULL;
		}
		(void) STRNCPY(path2, pathName);
		(void) sprintf(line, ".v%d", version);
		(void) STRNCAT(path2, line);
		(void) rename(pathName, path2);
		(void) fprintf(stderr, "%s: old version.\n", pathName);
		(void) fclose(fp);
		return NULL;
	}

	/* Sample line we're looking for:
	 * "Number of entries: 28" or "# # # 1"
	 */
	numBookmarks = -1;

	/* At the moment, we can't trust the number stored in the
	 * file.  It's there for future use.
	 */
	if (FGets(line, sizeof(line), fp) == NULL) {
		(void) fprintf(stderr, "%s: invalid format.\n", pathName);
		(void) fclose(fp);
		return NULL;
	}

	if (numBookmarks0 == (int *) 0) {
		/* If the caller doesn't care how many bookmarks are *really*
		 * in the file, then we can return now.
		 */
		return(fp);
	}

	/* Otherwise, we have to read through the whole file because
	 * unfortunately the header line can't be trusted.
	 */
	for (numBookmarks = 0; ; numBookmarks++) {
		if (GetNextBookmark(fp, &junkbm) < 0)
			break;
	}

	/* Now we have to re-open and re-position the file.
	 * We don't use rewind() because it doesn't always work.
	 * This introduces a race condition, but the bookmark
	 * functionality wasn't designed to be air-tight.
	 */
	CloseBookmarkFile(fp);
	fp = fopen(pathName, FOPEN_READ_TEXT);
	if (fp == NULL)
		return (NULL);
	if (FGets(line, sizeof(line), fp) == NULL) {
		(void) fprintf(stderr, "%s: invalid format.\n", pathName);
		(void) fclose(fp);
		return NULL;
	}

	if (FGets(line, sizeof(line), fp) == NULL) {
		(void) fprintf(stderr, "%s: invalid format.\n", pathName);
		(void) fclose(fp);
		return NULL;
	}

	/* NOW we're done. */
	*numBookmarks0 = numBookmarks;
	return (fp);
}