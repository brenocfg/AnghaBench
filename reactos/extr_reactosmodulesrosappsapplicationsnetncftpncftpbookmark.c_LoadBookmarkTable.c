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
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  Bookmark ;

/* Variables and functions */
 int /*<<< orphan*/  CloseBookmarkFile (int /*<<< orphan*/ *) ; 
 scalar_t__ GetNextBookmark (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OpenBookmarkFile (int*) ; 
 int /*<<< orphan*/  SortBookmarks () ; 
 int /*<<< orphan*/ * calloc (size_t,size_t) ; 
 int /*<<< orphan*/ * gBookmarkTable ; 
 int gNumBookmarks ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ realloc (int /*<<< orphan*/ *,size_t) ; 

int
LoadBookmarkTable(void)
{
	int i, nb;
	FILE *infp;

	infp = OpenBookmarkFile(&nb);
	if (infp == NULL) {
		nb = 0;
	}
	if ((nb != gNumBookmarks) && (gBookmarkTable != NULL)) {
		/* Re-loading the table from disk. */
		gBookmarkTable = (Bookmark *) realloc(gBookmarkTable, (size_t) (nb + 1) * sizeof(Bookmark));
		memset(gBookmarkTable, 0, (nb + 1) * sizeof(Bookmark));
	} else {
		gBookmarkTable = calloc((size_t) (nb + 1), (size_t) sizeof(Bookmark));
	}

	if (gBookmarkTable == NULL) {
		CloseBookmarkFile(infp);
		return (-1);
	}

	for (i=0; i<nb; i++) {
		if (GetNextBookmark(infp, gBookmarkTable + i) < 0) {
			break;
		}
	}
	gNumBookmarks = i;

	CloseBookmarkFile(infp);
	SortBookmarks();
	return (0);
}