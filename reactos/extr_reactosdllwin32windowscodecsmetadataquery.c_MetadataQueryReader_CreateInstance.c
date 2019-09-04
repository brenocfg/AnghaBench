#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_2__ IWICMetadataQueryReader_iface; int /*<<< orphan*/ * root; int /*<<< orphan*/ * block; } ;
typedef  TYPE_1__ QueryReader ;
typedef  TYPE_2__ IWICMetadataQueryReader ;
typedef  int /*<<< orphan*/  IWICMetadataBlockReader ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IWICMetadataBlockReader_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * heap_strdupW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mqr_vtbl ; 

HRESULT MetadataQueryReader_CreateInstance(IWICMetadataBlockReader *mbr, const WCHAR *root, IWICMetadataQueryReader **out)
{
    QueryReader *obj;

    obj = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*obj));
    if (!obj)
        return E_OUTOFMEMORY;

    obj->IWICMetadataQueryReader_iface.lpVtbl = &mqr_vtbl;
    obj->ref = 1;

    IWICMetadataBlockReader_AddRef(mbr);
    obj->block = mbr;

    obj->root = root ? heap_strdupW(root) : NULL;

    *out = &obj->IWICMetadataQueryReader_iface;

    return S_OK;
}