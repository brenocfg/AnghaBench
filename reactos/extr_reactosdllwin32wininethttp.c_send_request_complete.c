#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dwContext; } ;
struct TYPE_6__ {TYPE_4__ hdr; } ;
typedef  TYPE_1__ http_request_t ;
struct TYPE_7__ {int /*<<< orphan*/  dwError; int /*<<< orphan*/  dwResult; } ;
typedef  TYPE_2__ INTERNET_ASYNC_RESULT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  INTERNET_STATUS_REQUEST_COMPLETE ; 
 int /*<<< orphan*/  INTERNET_SendCallback (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 

__attribute__((used)) static void send_request_complete(http_request_t *req, DWORD_PTR result, DWORD error)
{
    INTERNET_ASYNC_RESULT iar;

    iar.dwResult = result;
    iar.dwError = error;

    INTERNET_SendCallback(&req->hdr, req->hdr.dwContext, INTERNET_STATUS_REQUEST_COMPLETE, &iar,
            sizeof(INTERNET_ASYNC_RESULT));
}