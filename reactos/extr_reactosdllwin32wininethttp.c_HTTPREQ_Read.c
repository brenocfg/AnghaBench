#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ read_size; scalar_t__ read_buf; scalar_t__ read_pos; int /*<<< orphan*/  read_section; } ;
typedef  TYPE_1__ http_request_t ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WSAEWOULDBLOCK ; 
 scalar_t__ drain_content (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_release_netconn (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 scalar_t__ read_http_stream (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD HTTPREQ_Read(http_request_t *req, void *buffer, DWORD size, DWORD *read, BOOL allow_blocking)
{
    DWORD current_read = 0, ret_read = 0;
    DWORD res = ERROR_SUCCESS;

    EnterCriticalSection( &req->read_section );

    if(req->read_size) {
        ret_read = min(size, req->read_size);
        memcpy(buffer, req->read_buf+req->read_pos, ret_read);
        req->read_size -= ret_read;
        req->read_pos += ret_read;
        allow_blocking = FALSE;
    }

    if(ret_read < size) {
        res = read_http_stream(req, (BYTE*)buffer+ret_read, size-ret_read, &current_read, allow_blocking);
        if(res == ERROR_SUCCESS)
            ret_read += current_read;
        else if(res == WSAEWOULDBLOCK && ret_read)
            res = ERROR_SUCCESS;
    }

    LeaveCriticalSection( &req->read_section );

    *read = ret_read;
    TRACE( "retrieved %u bytes (res %u)\n", ret_read, res );

    if(res != WSAEWOULDBLOCK) {
        if(res != ERROR_SUCCESS)
            http_release_netconn(req, FALSE);
        else if(!ret_read && drain_content(req, FALSE) == ERROR_SUCCESS)
            http_release_netconn(req, TRUE);
    }

    return res;
}