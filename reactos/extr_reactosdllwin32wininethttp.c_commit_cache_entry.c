#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* req_file; int /*<<< orphan*/  last_modified; int /*<<< orphan*/  expires; int /*<<< orphan*/ * hCacheFile; } ;
typedef  TYPE_2__ http_request_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  is_committed; int /*<<< orphan*/  file_name; int /*<<< orphan*/  url; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ CommitUrlCacheEntryW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  NORMAL_CACHE_ENTRY ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * build_response_header (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void commit_cache_entry(http_request_t *req)
{
    WCHAR *header;
    DWORD header_len;
    BOOL res;

    TRACE("%p\n", req);

    CloseHandle(req->hCacheFile);
    req->hCacheFile = NULL;

    header = build_response_header(req, TRUE);
    header_len = (header ? strlenW(header) : 0);
    res = CommitUrlCacheEntryW(req->req_file->url, req->req_file->file_name, req->expires,
             req->last_modified, NORMAL_CACHE_ENTRY,
            header, header_len, NULL, 0);
    if(res)
        req->req_file->is_committed = TRUE;
    else
        WARN("CommitUrlCacheEntry failed: %u\n", GetLastError());
    heap_free(header);
}