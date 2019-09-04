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
struct TYPE_3__ {int dwStructSize; int lpszSourceUrlName; int lpszLocalFileName; int lpszFileExtension; } ;
typedef  TYPE_1__ INTERNET_CACHE_ENTRY_INFOA ;

/* Variables and functions */
 char* filenameA ; 
 int /*<<< orphan*/  ok (int,char*,char const*,...) ; 
 int /*<<< orphan*/  strcmp (int,char*) ; 
 char* test_url ; 

__attribute__((used)) static void check_cache_entry_infoA(const char *returnedfrom, INTERNET_CACHE_ENTRY_INFOA *lpCacheEntryInfo)
{
    ok(lpCacheEntryInfo->dwStructSize == sizeof(*lpCacheEntryInfo), "%s: dwStructSize was %d\n", returnedfrom, lpCacheEntryInfo->dwStructSize);
    ok(!strcmp(lpCacheEntryInfo->lpszSourceUrlName, test_url), "%s: lpszSourceUrlName should be %s instead of %s\n", returnedfrom, test_url, lpCacheEntryInfo->lpszSourceUrlName);
    ok(!strcmp(lpCacheEntryInfo->lpszLocalFileName, filenameA), "%s: lpszLocalFileName should be %s instead of %s\n", returnedfrom, filenameA, lpCacheEntryInfo->lpszLocalFileName);
    ok(!strcmp(lpCacheEntryInfo->lpszFileExtension, "html"), "%s: lpszFileExtension should be html instead of %s\n", returnedfrom, lpCacheEntryInfo->lpszFileExtension);
}