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
typedef  int /*<<< orphan*/  Bookmark ;

/* Variables and functions */
 int /*<<< orphan*/  BookmarkSortProc ; 
 int /*<<< orphan*/ * gBookmarkTable ; 
 int gNumBookmarks ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 

void
SortBookmarks(void)
{
	if ((gBookmarkTable == NULL) || (gNumBookmarks < 2))
		return;

	/* Sorting involves swapping entire Bookmark structures.
	 * Normally the proper thing to do is to use an array
	 * of pointers to Bookmarks and sort them, but even
	 * these days a large bookmark list can be sorted in
	 * the blink of an eye.
	 */
	qsort(gBookmarkTable, (size_t) gNumBookmarks, sizeof(Bookmark), BookmarkSortProc);
}