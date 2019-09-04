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
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int ref; int allocated; TYPE_3__ IMXAttributes_iface; int /*<<< orphan*/  dispex; scalar_t__ length; void* attr; int /*<<< orphan*/  class_version; TYPE_2__ IVBSAXAttributes_iface; TYPE_1__ ISAXAttributes_iface; } ;
typedef  TYPE_4__ mxattributes ;
typedef  int /*<<< orphan*/  mxattribute ;
typedef  int /*<<< orphan*/  MSXML_VERSION ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  MXAttributesVtbl ; 
 int /*<<< orphan*/  SAXAttributesVtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,void*) ; 
 int /*<<< orphan*/  VBSAXAttributesVtbl ; 
 void* heap_alloc (int const) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxattrs_dispex ; 

HRESULT SAXAttributes_create(MSXML_VERSION version, void **ppObj)
{
    static const int default_count = 10;
    mxattributes *This;

    TRACE("(%p)\n", ppObj);

    This = heap_alloc( sizeof (*This) );
    if( !This )
        return E_OUTOFMEMORY;

    This->IMXAttributes_iface.lpVtbl = &MXAttributesVtbl;
    This->ISAXAttributes_iface.lpVtbl = &SAXAttributesVtbl;
    This->IVBSAXAttributes_iface.lpVtbl = &VBSAXAttributesVtbl;
    This->ref = 1;

    This->class_version = version;

    This->attr = heap_alloc(default_count*sizeof(mxattribute));
    This->length = 0;
    This->allocated = default_count;

    *ppObj = &This->IMXAttributes_iface;

    init_dispex(&This->dispex, (IUnknown*)&This->IMXAttributes_iface, &mxattrs_dispex);

    TRACE("returning iface %p\n", *ppObj);

    return S_OK;
}