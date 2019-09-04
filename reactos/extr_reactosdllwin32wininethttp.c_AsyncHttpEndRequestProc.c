#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_header_t ;
typedef  int /*<<< orphan*/  http_request_t ;
struct TYPE_3__ {scalar_t__ hdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  context; int /*<<< orphan*/  flags; TYPE_1__ hdr; } ;
typedef  TYPE_2__ end_request_task_t ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_HttpEndRequestW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void AsyncHttpEndRequestProc(task_header_t *hdr)
{
    end_request_task_t *task = (end_request_task_t*)hdr;
    http_request_t *req = (http_request_t*)task->hdr.hdr;

    TRACE("%p\n", req);

    HTTP_HttpEndRequestW(req, task->flags, task->context);
}