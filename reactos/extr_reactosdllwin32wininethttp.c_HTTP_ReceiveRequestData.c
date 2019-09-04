#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ hInternet; } ;
struct TYPE_13__ {scalar_t__ read_size; TYPE_3__ hdr; TYPE_2__* session; int /*<<< orphan*/  read_section; } ;
typedef  TYPE_4__ http_request_t ;
struct TYPE_10__ {int dwInternalFlags; } ;
struct TYPE_11__ {TYPE_1__ hdr; } ;
typedef  int DWORD_PTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int INET_OPENURL ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_4__*) ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ WSAEWOULDBLOCK ; 
 int /*<<< orphan*/  http_release_netconn (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ refill_read_buffer (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  send_request_complete (TYPE_4__*,int,scalar_t__) ; 

__attribute__((used)) static void HTTP_ReceiveRequestData(http_request_t *req)
{
    DWORD res, read = 0;

    TRACE("%p\n", req);

    EnterCriticalSection( &req->read_section );

    res = refill_read_buffer(req, FALSE, &read);
    if(res == ERROR_SUCCESS)
        read += req->read_size;

    LeaveCriticalSection( &req->read_section );

    if(res != WSAEWOULDBLOCK && (res != ERROR_SUCCESS || !read)) {
        WARN("res %u read %u, closing connection\n", res, read);
        http_release_netconn(req, FALSE);
    }

    if(res != ERROR_SUCCESS && res != WSAEWOULDBLOCK) {
        send_request_complete(req, 0, res);
        return;
    }

    send_request_complete(req, req->session->hdr.dwInternalFlags & INET_OPENURL ? (DWORD_PTR)req->hdr.hInternet : 1, 0);
}