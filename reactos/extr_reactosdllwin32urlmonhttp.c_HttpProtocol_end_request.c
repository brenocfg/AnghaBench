#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  request; } ;
typedef  TYPE_1__ Protocol ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_IO_PENDING ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  HttpEndRequestW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT HttpProtocol_end_request(Protocol *protocol)
{
    BOOL res;

    res = HttpEndRequestW(protocol->request, NULL, 0, 0);
    if(!res && GetLastError() != ERROR_IO_PENDING) {
        FIXME("HttpEndRequest failed: %u\n", GetLastError());
        return E_FAIL;
    }

    return S_OK;
}