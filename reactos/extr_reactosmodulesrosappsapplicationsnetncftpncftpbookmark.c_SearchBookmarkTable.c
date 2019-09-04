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
typedef  int /*<<< orphan*/  BookmarkPtr ;
typedef  int /*<<< orphan*/  Bookmark ;

/* Variables and functions */
 int /*<<< orphan*/  BookmarkSearchProc ; 
 scalar_t__ bsearch (char const*,int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gBookmarkTable ; 
 scalar_t__ gNumBookmarks ; 

BookmarkPtr
SearchBookmarkTable(const char *key)
{
	return ((BookmarkPtr) bsearch(key, gBookmarkTable, (size_t) gNumBookmarks, sizeof(Bookmark), BookmarkSearchProc));
}