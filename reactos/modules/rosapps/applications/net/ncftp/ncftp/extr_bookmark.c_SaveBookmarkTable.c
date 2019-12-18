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
struct TYPE_3__ {scalar_t__ deleted; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseBookmarkFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OpenTmpBookmarkFile (int) ; 
 scalar_t__ SwapBookmarkFiles () ; 
 scalar_t__ WriteBmLine (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* gBookmarkTable ; 
 int gNumBookmarks ; 

int
SaveBookmarkTable(void)
{
	int i;
	FILE *outfp;
	int nb;

	if ((gNumBookmarks < 1) || (gBookmarkTable == NULL))
		return (0);	/* Nothing to save. */

	/* Get a count of live bookmarks. */
	for (i=0, nb=0; i<gNumBookmarks; i++) {
		if (gBookmarkTable[i].deleted == 0)
			nb++;
	}
	outfp = OpenTmpBookmarkFile(nb);
	if (outfp == NULL) {
		return (-1);
	}

	for (i=0; i<gNumBookmarks; i++) {
		if (gBookmarkTable[i].deleted == 0) {
			if (WriteBmLine(gBookmarkTable + i, outfp, 1) < 0) {
				CloseBookmarkFile(outfp);
				return (-1);
			}
		}
	}
	CloseBookmarkFile(outfp);
	if (SwapBookmarkFiles() < 0) {
		return (-1);
	}
	return (0);
}