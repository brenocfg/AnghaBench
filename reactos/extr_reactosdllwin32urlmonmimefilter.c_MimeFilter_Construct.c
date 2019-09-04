#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int ref; TYPE_3__ IInternetProtocol_iface; TYPE_1__ IInternetProtocolSink_iface; } ;
typedef  TYPE_2__ MimeFilter ;
typedef  TYPE_3__* LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  InternetProtocolSinkVtbl ; 
 int /*<<< orphan*/  MimeFilterProtocolVtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  URLMON_LockModule () ; 
 TYPE_2__* heap_alloc_zero (int) ; 

HRESULT MimeFilter_Construct(IUnknown *pUnkOuter, LPVOID *ppobj)
{
    MimeFilter *ret;

    TRACE("(%p %p)\n", pUnkOuter, ppobj);

    URLMON_LockModule();

    ret = heap_alloc_zero(sizeof(MimeFilter));

    ret->IInternetProtocol_iface.lpVtbl = &MimeFilterProtocolVtbl;
    ret->IInternetProtocolSink_iface.lpVtbl = &InternetProtocolSinkVtbl;
    ret->ref = 1;

    *ppobj = &ret->IInternetProtocol_iface;
    return S_OK;
}