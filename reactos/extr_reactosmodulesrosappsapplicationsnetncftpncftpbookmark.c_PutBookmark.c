#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  line ;
struct TYPE_4__ {int /*<<< orphan*/  bookmarkName; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ Bookmark ;

/* Variables and functions */
 int /*<<< orphan*/  CloseBookmarkFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FGets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OpenBookmarkFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OpenTmpBookmarkFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRNCAT (char*,char*) ; 
 int /*<<< orphan*/  STRNCPY (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ SwapBookmarkFiles () ; 
 scalar_t__ WriteBmLine (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,size_t) ; 

int
PutBookmark(Bookmark *bmp, int savePassword)
{
	FILE *infp, *outfp;
	char line[256];
	char bmAbbr[64];
	int replaced = 0;
	size_t len;

	outfp = OpenTmpBookmarkFile(0);
	if (outfp == NULL)
		return (-1);

	(void) STRNCPY(bmAbbr, bmp->bookmarkName);
	(void) STRNCAT(bmAbbr, ",");
	len = strlen(bmAbbr);

	/* This may fail the first time we ever save a bookmark. */
	infp = OpenBookmarkFile(NULL);
	if (infp != NULL) {
		while (FGets(line, sizeof(line), infp) != NULL) {
			if (strncmp(line, bmAbbr, len) == 0) {
				/* Replace previous entry. */
				if (WriteBmLine(bmp, outfp, savePassword) < 0) {
					(void) fprintf(stderr, "Could not save bookmark.\n");
					perror("reason");
					(void) fclose(outfp);
				}
				replaced = 1;
			} else {
				if (fprintf(outfp, "%s\n", line) < 0) {
					(void) fprintf(stderr, "Could not save bookmark.\n");
					perror("reason");
					(void) fclose(outfp);
					return (-1);
				}
			}
		}
		CloseBookmarkFile(infp);
	}

	if (replaced == 0) {
		/* Add it as a new bookmark. */
		if (WriteBmLine(bmp, outfp, savePassword) < 0) {
			(void) fprintf(stderr, "Could not save bookmark.\n");
			perror("reason");
			(void) fclose(outfp);
			return (-1);
		}
	}

	if (fclose(outfp) < 0) {
		(void) fprintf(stderr, "Could not save bookmark.\n");
		perror("reason");
		return (-1);
	}

	if (SwapBookmarkFiles() < 0) {
		(void) fprintf(stderr, "Could not rename bookmark file.\n");
		perror("reason");
		return (-1);
	}
	return (0);
}