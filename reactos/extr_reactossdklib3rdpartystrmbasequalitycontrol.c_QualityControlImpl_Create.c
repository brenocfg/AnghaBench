#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int current_rstart; int current_rstop; int /*<<< orphan*/ * clock; int /*<<< orphan*/ * tonotify; int /*<<< orphan*/ * self; int /*<<< orphan*/ * input; } ;
typedef  TYPE_1__ QualityControlImpl ;
typedef  int /*<<< orphan*/  IPin ;
typedef  int /*<<< orphan*/  IBaseFilter ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,...) ; 

HRESULT QualityControlImpl_Create(IPin *input, IBaseFilter *self, QualityControlImpl **ppv)
{
    QualityControlImpl *This;
    TRACE("%p, %p, %p\n", input, self, ppv);
    *ppv = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(QualityControlImpl));
    if (!*ppv)
        return E_OUTOFMEMORY;
    This = *ppv;
    This->input = input;
    This->self = self;
    This->tonotify = NULL;
    This->clock = NULL;
    This->current_rstart = This->current_rstop = -1;
    TRACE("-> %p\n", This);
    return S_OK;
}