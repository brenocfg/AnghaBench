#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int /*<<< orphan*/ * vtbl; } ;
struct TYPE_14__ {int ref; TYPE_5__ IUnknown_outer; TYPE_5__* outer; int /*<<< orphan*/  https; TYPE_4__ IWinInetHttpInfo_iface; TYPE_3__ IInternetPriority_iface; TYPE_2__ IInternetProtocolEx_iface; TYPE_1__ base; } ;
typedef  TYPE_5__ IUnknown ;
typedef  TYPE_6__ HttpProtocol ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AsyncProtocolVtbl ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  HttpPriorityVtbl ; 
 int /*<<< orphan*/  HttpProtocolUnkVtbl ; 
 int /*<<< orphan*/  HttpProtocolVtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  URLMON_LockModule () ; 
 int /*<<< orphan*/  WinInetHttpInfoVtbl ; 
 TYPE_6__* heap_alloc_zero (int) ; 

__attribute__((used)) static HRESULT create_http_protocol(BOOL https, IUnknown *outer, void **ppobj)
{
    HttpProtocol *ret;

    ret = heap_alloc_zero(sizeof(HttpProtocol));
    if(!ret)
        return E_OUTOFMEMORY;

    ret->base.vtbl = &AsyncProtocolVtbl;
    ret->IUnknown_outer.lpVtbl            = &HttpProtocolUnkVtbl;
    ret->IInternetProtocolEx_iface.lpVtbl = &HttpProtocolVtbl;
    ret->IInternetPriority_iface.lpVtbl   = &HttpPriorityVtbl;
    ret->IWinInetHttpInfo_iface.lpVtbl    = &WinInetHttpInfoVtbl;

    ret->https = https;
    ret->ref = 1;
    ret->outer = outer ? outer : &ret->IUnknown_outer;

    *ppobj = &ret->IUnknown_outer;

    URLMON_LockModule();
    return S_OK;
}