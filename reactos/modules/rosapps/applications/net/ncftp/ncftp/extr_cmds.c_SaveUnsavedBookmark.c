#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  url ;
typedef  int /*<<< orphan*/  ans ;
struct TYPE_5__ {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  BookmarkToURL (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  FillBookmarkInfo (TYPE_1__*) ; 
 scalar_t__ PromptForBookmarkName (TYPE_1__*) ; 
 int /*<<< orphan*/  SaveCurrentAsBookmark () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gAutoSaveChangesToExistingBookmarks ; 
 TYPE_1__ gBm ; 
 scalar_t__ gConfirmClose ; 
 int gLoadedBm ; 
 char* gOurDirectoryPath ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

void
SaveUnsavedBookmark(void)
{
	char url[256];
	char ans[64];
	int c;

	if ((gConfirmClose != 0) && (gLoadedBm == 0) && (gOurDirectoryPath[0] != '\0')) {
		FillBookmarkInfo(&gBm);
		BookmarkToURL(&gBm, url, sizeof(url));
		(void) printf("\n\nYou have not saved a bookmark for this site.\n");
		(void) sleep(1);
		(void) printf("\nWould you like to save a bookmark to:\n\t%s\n\n", url);
		for (;;) {
			(void) printf("Save? (yes/no) ");
			(void) memset(ans, 0, sizeof(ans));
			fflush(stdin);
			if (fgets(ans, sizeof(ans) - 1, stdin) == NULL) {
				c = 'n';
				break;
			}
			c = ans[0];
			if ((c == 'n') || (c == 'y'))
				break;
			if (c == 'N') {
				c = 'n';
				break;
			} else if (c == 'Y') {
				c = 'y';
				break;
			}
		}
		if (c == 'n') {
			(void) printf("Not saved.  (If you don't want to be asked this, \"set confirm-close no\")\n\n\n");

		} else if (PromptForBookmarkName(&gBm) < 0) {
			(void) printf("Nevermind.\n");
		} else {
			SaveCurrentAsBookmark();
		}
	} else if ((gLoadedBm == 1) && (gOurDirectoryPath[0] != '\0') && (strcmp(gOurDirectoryPath, gBm.dir) != 0)) {
		/* Bookmark has changed. */
		if (gAutoSaveChangesToExistingBookmarks != 0) {
			SaveCurrentAsBookmark();
		}
	}
}