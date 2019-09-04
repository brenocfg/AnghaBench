#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dfltname ;
typedef  int /*<<< orphan*/  bmname ;
struct TYPE_5__ {int /*<<< orphan*/  host; } ;
struct TYPE_4__ {int /*<<< orphan*/  bookmarkName; } ;
typedef  TYPE_1__* BookmarkPtr ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultBookmarkName (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FGets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRNCPY (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 TYPE_2__ gConn ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdin ; 

int
PromptForBookmarkName(BookmarkPtr bmp)
{
	char dfltname[64];
	char bmname[64];

	DefaultBookmarkName(dfltname, sizeof(dfltname), gConn.host);
	if (dfltname[0] == '\0') {
		(void) printf("Enter a name for this bookmark: ");
	} else {
		(void) printf("Enter a name for this bookmark, or hit enter for \"%s\": ", dfltname);
	}
	fflush(stdin);
	(void) FGets(bmname, sizeof(bmname), stdin);
	if (bmname[0] != '\0') {
		(void) STRNCPY(bmp->bookmarkName, bmname);
		return (0);
	} else if (dfltname[0] != '\0') {
		(void) STRNCPY(bmp->bookmarkName, dfltname);
		return (0);
	}
	return (-1);
}