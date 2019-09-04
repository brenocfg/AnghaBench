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
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_1__ IMimeSecurity_iface; } ;
typedef  TYPE_2__ MimeSecurity ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MimeSecurityVtbl ; 
 int /*<<< orphan*/  S_OK ; 

HRESULT MimeSecurity_create(IUnknown *outer, void **obj)
{
    MimeSecurity *This;

    *obj = NULL;

    if (outer) return CLASS_E_NOAGGREGATION;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(*This));
    if (!This) return E_OUTOFMEMORY;

    This->IMimeSecurity_iface.lpVtbl = &MimeSecurityVtbl;
    This->ref = 1;

    *obj = &This->IMimeSecurity_iface;
    return S_OK;
}