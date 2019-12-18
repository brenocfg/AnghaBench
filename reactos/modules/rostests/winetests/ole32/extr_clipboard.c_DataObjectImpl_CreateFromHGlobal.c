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
struct TYPE_5__ {int ref; int fmtetc_cnt; TYPE_1__ IDataObject_iface; int /*<<< orphan*/ * fmtetc; int /*<<< orphan*/ * hmfp; int /*<<< orphan*/ * stg; int /*<<< orphan*/ * stm; int /*<<< orphan*/  text; } ;
typedef  TYPE_1__* LPDATAOBJECT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  int /*<<< orphan*/  FORMATETC ;
typedef  TYPE_2__ DataObjectImpl ;

/* Variables and functions */
 int /*<<< orphan*/  CF_TEXT ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InitFormatEtc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TYMED_HGLOBAL ; 
 int /*<<< orphan*/  VT_DataObjectImpl ; 

__attribute__((used)) static HRESULT DataObjectImpl_CreateFromHGlobal(HGLOBAL text, LPDATAOBJECT *dataobj)
{
    DataObjectImpl *obj;

    obj = HeapAlloc(GetProcessHeap(), 0, sizeof(DataObjectImpl));
    obj->IDataObject_iface.lpVtbl = &VT_DataObjectImpl;
    obj->ref = 1;
    obj->text = text;
    obj->stm = NULL;
    obj->stg = NULL;
    obj->hmfp = NULL;

    obj->fmtetc_cnt = 1;
    obj->fmtetc = HeapAlloc(GetProcessHeap(), 0, obj->fmtetc_cnt*sizeof(FORMATETC));
    InitFormatEtc(obj->fmtetc[0], CF_TEXT, TYMED_HGLOBAL);

    *dataobj = &obj->IDataObject_iface;
    return S_OK;
}