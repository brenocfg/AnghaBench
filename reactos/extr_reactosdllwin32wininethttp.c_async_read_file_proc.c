#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_header_t ;
struct TYPE_10__ {scalar_t__ hdr; } ;
struct TYPE_11__ {scalar_t__ read_pos; scalar_t__ size; scalar_t__* ret_read; scalar_t__ buf; TYPE_1__ hdr; } ;
typedef  TYPE_2__ read_file_task_t ;
typedef  int /*<<< orphan*/  read ;
struct TYPE_13__ {int /*<<< orphan*/  dwContext; } ;
struct TYPE_12__ {TYPE_8__ hdr; int /*<<< orphan*/  read_section; } ;
typedef  TYPE_3__ http_request_t ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HTTPREQ_Read (TYPE_3__*,char*,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTERNET_STATUS_RESPONSE_RECEIVED ; 
 int /*<<< orphan*/  INTERNET_SendCallback (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ drain_content (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_release_netconn (TYPE_3__*,int) ; 
 scalar_t__ refill_read_buffer (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  send_request_complete (TYPE_3__*,int,scalar_t__) ; 

__attribute__((used)) static void async_read_file_proc(task_header_t *hdr)
{
    read_file_task_t *task = (read_file_task_t*)hdr;
    http_request_t *req = (http_request_t*)task->hdr.hdr;
    DWORD res = ERROR_SUCCESS, read = task->read_pos, complete_arg = 0;

    TRACE("req %p buf %p size %u read_pos %u ret_read %p\n", req, task->buf, task->size, task->read_pos, task->ret_read);

    if(task->buf) {
        DWORD read_bytes;
        while (read < task->size) {
            res = HTTPREQ_Read(req, (char*)task->buf + read, task->size - read, &read_bytes, TRUE);
            if (res != ERROR_SUCCESS || !read_bytes)
                break;
            read += read_bytes;
        }
    }else {
        EnterCriticalSection(&req->read_section);
        res = refill_read_buffer(req, TRUE, &read);
        LeaveCriticalSection(&req->read_section);

        if(task->ret_read)
            complete_arg = read; /* QueryDataAvailable reports read bytes in request complete notification */
        if(res != ERROR_SUCCESS || !read)
            http_release_netconn(req, drain_content(req, FALSE) == ERROR_SUCCESS);
    }

    TRACE("res %u read %u\n", res, read);

    if(task->ret_read)
        *task->ret_read = read;

    /* FIXME: We should report bytes transferred before decoding content. */
    INTERNET_SendCallback(&req->hdr, req->hdr.dwContext, INTERNET_STATUS_RESPONSE_RECEIVED, &read, sizeof(read));

    if(res != ERROR_SUCCESS)
        complete_arg = res;
    send_request_complete(req, res == ERROR_SUCCESS, complete_arg);
}