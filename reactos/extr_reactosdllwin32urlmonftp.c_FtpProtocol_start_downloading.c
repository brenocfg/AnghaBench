#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  content_length; int /*<<< orphan*/  request; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  Protocol ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ FtpProtocol ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FtpGetFileSize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* impl_from_Protocol (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT FtpProtocol_start_downloading(Protocol *prot)
{
    FtpProtocol *This = impl_from_Protocol(prot);
    DWORD size;
    BOOL res;

    res = FtpGetFileSize(This->base.request, &size);
    if(res)
        This->base.content_length = size;
    else
        WARN("FtpGetFileSize failed: %d\n", GetLastError());

    return S_OK;
}