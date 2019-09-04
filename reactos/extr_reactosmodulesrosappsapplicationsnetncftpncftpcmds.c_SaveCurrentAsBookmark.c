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
typedef  int /*<<< orphan*/  ans ;
struct TYPE_4__ {char* pass; char* bookmarkName; } ;

/* Variables and functions */
 int /*<<< orphan*/  FillBookmarkInfo (TYPE_1__*) ; 
 scalar_t__ PutBookmark (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ReCacheBookmarks () ; 
 int StrToBool (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ gBm ; 
 int gLoadedBm ; 
 int gSavePasswords ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 

void
SaveCurrentAsBookmark(void)
{
	int saveBm;
	char ans[64];

	/* gBm.bookmarkName must already be set. */
	FillBookmarkInfo(&gBm);

	saveBm = gSavePasswords;
	if (gLoadedBm != 0)
		saveBm = 1;
	if ((saveBm < 0) && (gBm.pass[0] != '\0')) {
		(void) printf("\n\nYou logged into this site using a password.\nWould you like to save the password with this bookmark?\n\n");
		(void) printf("Save? [no] ");
		(void) memset(ans, 0, sizeof(ans));
		fflush(stdin);
		(void) fgets(ans, sizeof(ans) - 1, stdin);
		if ((saveBm = StrToBool(ans)) == 0) {
			(void) printf("\nNot saving the password.\n");
		}
	}
	if (PutBookmark(&gBm, saveBm) < 0) {
		(void) fprintf(stderr, "Could not save bookmark.\n");
	} else {
		/* Also marks whether we saved it. */
		gLoadedBm = 1;
		(void) printf("Bookmark \"%s\" saved.\n", gBm.bookmarkName);

		ReCacheBookmarks();
	}
}