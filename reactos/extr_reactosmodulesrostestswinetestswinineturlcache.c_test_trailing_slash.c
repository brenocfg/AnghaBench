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
typedef  int /*<<< orphan*/  zero_byte ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int CommitUrlCacheEntryA (char*,int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int CreateUrlCacheEntryA (char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int DeleteUrlCacheEntryA (char*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  NORMAL_CACHE_ENTRY ; 
 int cache_entry_exists (char*) ; 
 int /*<<< orphan*/  create_and_write_file (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_trailing_slash(void)
{
    char filename[MAX_PATH];
    BYTE zero_byte = 0;
    BOOL ret;

    static const FILETIME filetime_zero;
    static char url_with_slash[] = "http://testing.cache.com/";


    ret = CreateUrlCacheEntryA(url_with_slash, 0, "html", filename, 0);
    ok(ret, "CreateUrlCacheEntry failed with error %d\n", GetLastError());

    create_and_write_file(filename, &zero_byte, sizeof(zero_byte));

    ret = CommitUrlCacheEntryA("Visited: http://testing.cache.com/", NULL, filetime_zero, filetime_zero,
            NORMAL_CACHE_ENTRY, NULL, 0, "html", NULL);
    ok(ret, "CommitUrlCacheEntry failed with error %d\n", GetLastError());

    ok(cache_entry_exists("Visited: http://testing.cache.com/"), "cache entry does not exist\n");
    ok(!cache_entry_exists("Visited: http://testing.cache.com"), "cache entry exists\n");

    ret = DeleteUrlCacheEntryA("Visited: http://testing.cache.com/");
    ok(ret, "DeleteCacheEntryA failed\n");
    DeleteFileA(filename);
}