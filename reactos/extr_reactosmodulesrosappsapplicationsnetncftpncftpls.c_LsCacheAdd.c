#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* itempath; scalar_t__ hits; int /*<<< orphan*/  expiration; int /*<<< orphan*/  fil; } ;
struct TYPE_5__ {scalar_t__ nFileInfos; } ;
typedef  TYPE_1__* FileInfoListPtr ;
typedef  int /*<<< orphan*/  FileInfoList ;

/* Variables and functions */
 int /*<<< orphan*/  FlushLsCacheItem (int) ; 
 int LsCacheLookup (char const* const) ; 
 char* StrDup (char const* const) ; 
 int /*<<< orphan*/  Trace (int,char*,char const* const) ; 
 TYPE_3__* gLsCache ; 
 scalar_t__ gLsCacheItemLifetime ; 
 int gOldestLsCacheItem ; 
 int kLsCacheSize ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
LsCacheAdd(const char *const itempath, FileInfoListPtr files)
{
	char *cp;
	int j;

	/* Never cache empty listings in case of errors */
	if (files->nFileInfos == 0)
		return;

	j = LsCacheLookup(itempath);
	if (j >= 0) {
		/* Directory was already in there;
		 * Replace it with the new
		 * contents.
		 */
		FlushLsCacheItem(j);
	}

	cp = StrDup(itempath);
	if (cp == NULL)
		return;

	j = gOldestLsCacheItem;
	(void) memcpy(&gLsCache[j].fil, files, sizeof(FileInfoList));
	(void) time(&gLsCache[j].expiration);
	gLsCache[j].expiration += gLsCacheItemLifetime;
	gLsCache[j].hits = 0;
	gLsCache[j].itempath = cp;
	Trace(1, "ls cache add: %s\n", itempath);

	/* Increment the pointer.  This is a circular array, so if it
	 * hits the end it wraps over to the other side.
	 */
	gOldestLsCacheItem++;
	if (gOldestLsCacheItem >= kLsCacheSize)
		gOldestLsCacheItem = 0;
}