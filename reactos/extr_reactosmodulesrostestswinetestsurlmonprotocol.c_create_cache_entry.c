#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  content ;
typedef  int /*<<< orphan*/  cache_headers ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  LowPart; int /*<<< orphan*/  HighPart; } ;
struct TYPE_8__ {int QuadPart; TYPE_1__ u; } ;
typedef  TYPE_2__ ULARGE_INTEGER ;
struct TYPE_9__ {int /*<<< orphan*/  dwLowDateTime; int /*<<< orphan*/  dwHighDateTime; } ;
typedef  int LONGLONG ;
typedef  scalar_t__ HANDLE ;
typedef  TYPE_3__ FILETIME ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  char BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  CommitUrlCacheEntryA (char const*,char*,TYPE_3__,TYPE_3__,int /*<<< orphan*/ ,char*,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateUrlCacheEntryA (char const*,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetSystemTimeAsFileTime (TYPE_3__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  NORMAL_CACHE_ENTRY ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*) ; 
 char* w2a (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void create_cache_entry(const WCHAR *urlw)
{
    FILETIME now, tomorrow, yesterday;
    char file_path[MAX_PATH];
    BYTE content[1000];
    ULARGE_INTEGER li;
    const char *url;
    HANDLE file;
    DWORD size;
    unsigned i;
    BOOL res;

    BYTE cache_headers[] = "HTTP/1.1 200 OK\r\n\r\n";

    trace("Testing cache read...\n");

    url = w2a(urlw);

    for(i = 0; i < sizeof(content); i++)
        content[i] = '0' + (i%10);

    GetSystemTimeAsFileTime(&now);
    li.u.HighPart = now.dwHighDateTime;
    li.u.LowPart = now.dwLowDateTime;
    li.QuadPart += (LONGLONG)10000000 * 3600 * 24;
    tomorrow.dwHighDateTime = li.u.HighPart;
    tomorrow.dwLowDateTime = li.u.LowPart;
    li.QuadPart -= (LONGLONG)10000000 * 3600 * 24 * 2;
    yesterday.dwHighDateTime = li.u.HighPart;
    yesterday.dwLowDateTime = li.u.LowPart;

    res = CreateUrlCacheEntryA(url, sizeof(content), "", file_path, 0);
    ok(res, "CreateUrlCacheEntryA failed: %u\n", GetLastError());

    file = CreateFileA(file_path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    ok(file != INVALID_HANDLE_VALUE, "CreateFile failed\n");

    WriteFile(file, content, sizeof(content), &size, NULL);
    CloseHandle(file);

    res = CommitUrlCacheEntryA(url, file_path, tomorrow, yesterday, NORMAL_CACHE_ENTRY,
                               cache_headers, sizeof(cache_headers)-1, "", 0);
    ok(res, "CommitUrlCacheEntryA failed: %u\n", GetLastError());
}