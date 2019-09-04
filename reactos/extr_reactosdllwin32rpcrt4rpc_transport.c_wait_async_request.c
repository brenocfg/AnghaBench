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
struct TYPE_4__ {scalar_t__ async_result; int /*<<< orphan*/  completion_event; } ;
typedef  TYPE_1__ RpcHttpAsyncData ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_NCACN_HTTP_TIMEOUT ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 scalar_t__ ERROR_IO_PENDING ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  RPC_S_CALL_CANCELLED ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  RPC_S_SERVER_UNAVAILABLE ; 
 int /*<<< orphan*/  RpcHttpAsyncData_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForMultipleObjects (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static RPC_STATUS wait_async_request(RpcHttpAsyncData *async_data, BOOL call_ret, HANDLE cancel_event)
{
    HANDLE handles[2] = { async_data->completion_event, cancel_event };
    DWORD res;

    if(call_ret) {
        RpcHttpAsyncData_Release(async_data);
        return RPC_S_OK;
    }

    if(GetLastError() != ERROR_IO_PENDING) {
        RpcHttpAsyncData_Release(async_data);
        ERR("Request failed with error %d\n", GetLastError());
        return RPC_S_SERVER_UNAVAILABLE;
    }

    res = WaitForMultipleObjects(2, handles, FALSE, DEFAULT_NCACN_HTTP_TIMEOUT);
    if(res != WAIT_OBJECT_0) {
        TRACE("Cancelled\n");
        return RPC_S_CALL_CANCELLED;
    }

    if(async_data->async_result) {
        ERR("Async request failed with error %d\n", async_data->async_result);
        return RPC_S_SERVER_UNAVAILABLE;
    }

    return RPC_S_OK;
}