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
typedef  int /*<<< orphan*/  url ;
typedef  scalar_t__ sigproc_t ;
struct TYPE_4__ {char* bookmarkName; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ Bookmark ;

/* Variables and functions */
 int /*<<< orphan*/  BookmarkToURL (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  CloseBookmarkFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ClosePager (int /*<<< orphan*/ *) ; 
 scalar_t__ GetNextBookmark (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ NcSignal (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * OpenBookmarkFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OpenPager () ; 
 int /*<<< orphan*/  SIGPIPE ; 
 scalar_t__ SIG_IGN ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int
PrintHosts(void)
{
	FILE *bookmarks;
	FILE *pager;
	int nbm = 0;
	Bookmark bm;
	char url[128];
#ifdef SIGPIPE
	sigproc_t osigpipe;
#endif

	bookmarks = OpenBookmarkFile(NULL);
	if (bookmarks == NULL)
		return (0);

#ifdef SIGPIPE
	osigpipe = (sigproc_t) NcSignal(SIGPIPE, SIG_IGN);
#endif
	pager = OpenPager();

	while (GetNextBookmark(bookmarks, &bm) == 0) {
		nbm++;
		if (nbm == 1) {
			/* header */
			(void) fprintf(pager, "--BOOKMARK----------URL--------------------------------------------------------\n");
		}
		BookmarkToURL(&bm, url, sizeof(url));
		(void) fprintf(pager, "  %-16s  %s\n", bm.bookmarkName, url);
	}

	ClosePager(pager);
	CloseBookmarkFile(bookmarks);

#ifdef SIGPIPE
	(void) NcSignal(SIGPIPE, osigpipe);
#endif
	return (nbm);
}