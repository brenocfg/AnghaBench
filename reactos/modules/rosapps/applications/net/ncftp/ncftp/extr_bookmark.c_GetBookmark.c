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
typedef  int /*<<< orphan*/  line ;
struct TYPE_5__ {char* bookmarkName; char* name; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ Bookmark ;

/* Variables and functions */
 int /*<<< orphan*/  CloseBookmarkFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FGets (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ISTREQ (char*,char const* const) ; 
 scalar_t__ ISTRNEQ (char*,char const* const,size_t) ; 
 int /*<<< orphan*/ * OpenBookmarkFile (int /*<<< orphan*/ *) ; 
 scalar_t__ ParseHostLine (char*,TYPE_1__*) ; 
 scalar_t__ gBookmarkMatchMode ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char const* const) ; 

int
GetBookmark(const char *const bmabbr, Bookmark *bmp)
{
	FILE *fp;
	char line[512];
	Bookmark byHostName;
	Bookmark byHostAbbr;
	Bookmark byBmAbbr;
	size_t byBmNameFlag = 0;
	size_t byBmAbbrFlag = 0;
	size_t byHostNameFlag = 0;
	size_t byHostAbbrFlag = 0;
	int result = -1;
	int exactMatch = 0;
	size_t bmabbrLen;
	char *cp;

	fp = OpenBookmarkFile(NULL);
	if (fp == NULL)
		return (-1);

	bmabbrLen = strlen(bmabbr);
	while (FGets(line, sizeof(line), fp) != NULL) {
		if (ParseHostLine(line, bmp) < 0)
			continue;
		if (ISTREQ(bmp->bookmarkName, bmabbr)) {
			/* Exact match, done. */
			byBmNameFlag = bmabbrLen;
			exactMatch = 1;
			break;
		} else if (ISTRNEQ(bmp->bookmarkName, bmabbr, bmabbrLen)) {
			/* Remember this one, it matched an abbreviated
			 * bookmark name.
			 */
			byBmAbbr = *bmp;
			byBmAbbrFlag = bmabbrLen;
		} else if (ISTREQ(bmp->name, bmabbr)) {
			/* Remember this one, it matched a full
			 * host name.
			 */
			byHostName = *bmp;
			byHostNameFlag = bmabbrLen;
		} else if ((cp = strchr(bmp->name, '.')) != NULL) {
			/* See if it matched part of the hostname. */
			if (ISTRNEQ(bmp->name, "ftp", 3)) {
				cp = cp + 1;
			} else if (ISTRNEQ(bmp->name, "www", 3)) {
				cp = cp + 1;
			} else {
				cp = bmp->name;
			}
			if (ISTRNEQ(cp, bmabbr, bmabbrLen)) {
				/* Remember this one, it matched a full
				 * host name.
				 */
				byHostAbbr = *bmp;
				byHostAbbrFlag = bmabbrLen;
			}
		}
	}

	if (gBookmarkMatchMode == 0) {
		/* Only use a bookmark when the exact
		 * bookmark name was used.
		 */
		if (exactMatch != 0) {
			result = 0;
		}
	} else {
		/* Pick the best match, if any. */
		if (byBmNameFlag != 0) {
			/* *bmp is already set. */
			result = 0;
		} else if (byBmAbbrFlag != 0) {
			result = 0;
			*bmp = byBmAbbr;
		} else if (byHostNameFlag != 0) {
			result = 0;
			*bmp = byHostName;
		} else if (byHostAbbrFlag != 0) {
			result = 0;
			*bmp = byHostAbbr;
		}
	}

	if (result != 0)
		memset(bmp, 0, sizeof(Bookmark));

	CloseBookmarkFile(fp);
	return (result);
}