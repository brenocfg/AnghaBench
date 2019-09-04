#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {scalar_t__* Spare; } ;
struct TYPE_22__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_21__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_23__ {TYPE_7__ IInternetProtocolSink_iface; TYPE_6__ IInternetProtocol_iface; } ;
struct TYPE_20__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_19__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_18__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_17__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_16__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {TYPE_9__* DebugInfo; } ;
struct TYPE_14__ {int ref; TYPE_13__ section; TYPE_8__ default_protocol_handler; TYPE_7__* protocol_sink_handler; TYPE_6__* protocol_handler; int /*<<< orphan*/  notif_hwnd; int /*<<< orphan*/  apartment_thread; TYPE_5__ IInternetProtocolSink_iface; TYPE_4__ IServiceProvider_iface; TYPE_3__ IInternetPriority_iface; TYPE_2__ IInternetBindInfo_iface; TYPE_1__ IInternetProtocolEx_iface; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD_PTR ;
typedef  TYPE_10__ BindProtocol ;

/* Variables and functions */
 int /*<<< orphan*/  BindProtocolVtbl ; 
 int /*<<< orphan*/  GetCurrentThreadId () ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_13__*) ; 
 int /*<<< orphan*/  InternetBindInfoVtbl ; 
 int /*<<< orphan*/  InternetPriorityVtbl ; 
 int /*<<< orphan*/  InternetProtocolHandlerVtbl ; 
 int /*<<< orphan*/  InternetProtocolSinkHandlerVtbl ; 
 int /*<<< orphan*/  InternetProtocolSinkVtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  ServiceProviderVtbl ; 
 int /*<<< orphan*/  URLMON_LockModule () ; 
 int /*<<< orphan*/  get_notif_hwnd () ; 
 TYPE_10__* heap_alloc_zero (int) ; 

HRESULT create_binding_protocol(BindProtocol **protocol)
{
    BindProtocol *ret = heap_alloc_zero(sizeof(BindProtocol));

    ret->IInternetProtocolEx_iface.lpVtbl   = &BindProtocolVtbl;
    ret->IInternetBindInfo_iface.lpVtbl     = &InternetBindInfoVtbl;
    ret->IInternetPriority_iface.lpVtbl     = &InternetPriorityVtbl;
    ret->IServiceProvider_iface.lpVtbl      = &ServiceProviderVtbl;
    ret->IInternetProtocolSink_iface.lpVtbl = &InternetProtocolSinkVtbl;

    ret->default_protocol_handler.IInternetProtocol_iface.lpVtbl = &InternetProtocolHandlerVtbl;
    ret->default_protocol_handler.IInternetProtocolSink_iface.lpVtbl = &InternetProtocolSinkHandlerVtbl;

    ret->ref = 1;
    ret->apartment_thread = GetCurrentThreadId();
    ret->notif_hwnd = get_notif_hwnd();
    ret->protocol_handler = &ret->default_protocol_handler.IInternetProtocol_iface;
    ret->protocol_sink_handler = &ret->default_protocol_handler.IInternetProtocolSink_iface;
    InitializeCriticalSection(&ret->section);
    ret->section.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": BindProtocol.section");

    URLMON_LockModule();

    *protocol = ret;
    return S_OK;
}