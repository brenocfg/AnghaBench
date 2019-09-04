#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int read_size; int read_pos; int read_buf; } ;
typedef  TYPE_1__ http_request_t ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  memmove (int,int,int) ; 
 scalar_t__ read_http_stream (TYPE_1__*,int,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD refill_read_buffer(http_request_t *req, BOOL allow_blocking, DWORD *read_bytes)
{
    DWORD res, read=0;

    if(req->read_size == sizeof(req->read_buf))
        return ERROR_SUCCESS;

    if(req->read_pos) {
        if(req->read_size)
            memmove(req->read_buf, req->read_buf+req->read_pos, req->read_size);
        req->read_pos = 0;
    }

    res = read_http_stream(req, req->read_buf+req->read_size, sizeof(req->read_buf) - req->read_size,
            &read, allow_blocking);
    if(res != ERROR_SUCCESS)
        return res;

    req->read_size += read;

    TRACE("read %u bytes, read_size %u\n", read, req->read_size);
    if(read_bytes)
        *read_bytes = read;
    return res;
}