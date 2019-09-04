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
struct TYPE_4__ {int /*<<< orphan*/  completion_event; } ;
typedef  TYPE_1__ RpcHttpAsyncData ;

/* Variables and functions */
 int /*<<< orphan*/  ResetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RpcHttpAsyncData_AddRef (TYPE_1__*) ; 

__attribute__((used)) static void prepare_async_request(RpcHttpAsyncData *async_data)
{
    ResetEvent(async_data->completion_event);
    RpcHttpAsyncData_AddRef(async_data);
}