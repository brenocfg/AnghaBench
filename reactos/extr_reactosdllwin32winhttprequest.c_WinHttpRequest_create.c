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
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {TYPE_2__* DebugInfo; } ;
struct TYPE_5__ {int /*<<< orphan*/ * lpszProxyBypass; int /*<<< orphan*/ * lpszProxy; } ;
struct winhttp_request {int refs; TYPE_3__ IWinHttpRequest_iface; TYPE_4__ cs; int /*<<< orphan*/  url_codepage; TYPE_1__ proxy; int /*<<< orphan*/  state; } ;
struct TYPE_6__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_4__*) ; 
 int /*<<< orphan*/  REQUEST_STATE_UNINITIALIZED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,void*) ; 
 struct winhttp_request* heap_alloc (int) ; 
 int /*<<< orphan*/  winhttp_request_vtbl ; 

HRESULT WinHttpRequest_create( void **obj )
{
    struct winhttp_request *request;

    TRACE("%p\n", obj);

    if (!(request = heap_alloc( sizeof(*request) ))) return E_OUTOFMEMORY;
    request->IWinHttpRequest_iface.lpVtbl = &winhttp_request_vtbl;
    request->refs = 1;
    request->state = REQUEST_STATE_UNINITIALIZED;
    request->proxy.lpszProxy = NULL;
    request->proxy.lpszProxyBypass = NULL;
    request->url_codepage = CP_UTF8;
    InitializeCriticalSection( &request->cs );
    request->cs.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": winhttp_request.cs");

    *obj = &request->IWinHttpRequest_iface;
    TRACE("returning iface %p\n", *obj);
    return S_OK;
}