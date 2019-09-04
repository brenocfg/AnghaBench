#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_15__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_18__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_24__ {TYPE_15__ IPin_iface; int /*<<< orphan*/ * pair; TYPE_7__* sg; int /*<<< orphan*/  name; int /*<<< orphan*/  dir; } ;
struct TYPE_23__ {int /*<<< orphan*/  formattype; int /*<<< orphan*/  subtype; int /*<<< orphan*/  majortype; } ;
struct TYPE_21__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_22__ {int /*<<< orphan*/ * pair; TYPE_7__* sg; int /*<<< orphan*/  name; int /*<<< orphan*/  dir; TYPE_3__ IPin_iface; } ;
struct TYPE_20__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_19__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_25__ {int grabberMethod; int bufferLen; TYPE_8__ IUnknown_inner; TYPE_6__ pin_in; int /*<<< orphan*/  seekthru_unk; TYPE_8__* outer_unk; int /*<<< orphan*/ * bufferData; int /*<<< orphan*/  oneShot; int /*<<< orphan*/ * grabberIface; int /*<<< orphan*/ * memOutput; int /*<<< orphan*/ * allocator; TYPE_5__ mtype; TYPE_4__ pin_out; TYPE_2__ IMemInputPin_iface; TYPE_1__ ISampleGrabber_iface; int /*<<< orphan*/  filter; } ;
typedef  TYPE_7__ SG_Impl ;
typedef  TYPE_8__* LPVOID ;
typedef  TYPE_8__ IUnknown ;
typedef  int /*<<< orphan*/  ISeekingPassThru ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  BaseFilter_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_SampleGrabber ; 
 int /*<<< orphan*/  CLSID_SeekingPassThru ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 TYPE_7__* CoTaskMemAlloc (int) ; 
 scalar_t__ E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FORMAT_None ; 
 int /*<<< orphan*/  GUID_NULL ; 
 int /*<<< orphan*/  IBaseFilter_VTable ; 
 int /*<<< orphan*/  IID_ISeekingPassThru ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IMemInputPin_VTable ; 
 int /*<<< orphan*/  IPin_In_VTable ; 
 int /*<<< orphan*/  IPin_Out_VTable ; 
 int /*<<< orphan*/  ISampleGrabber_VTable ; 
 int /*<<< orphan*/  ISeekingPassThru_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_15__*) ; 
 int /*<<< orphan*/  ISeekingPassThru_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  MEDIASUBTYPE_None ; 
 int /*<<< orphan*/  OneShot_None ; 
 int /*<<< orphan*/  PINDIR_INPUT ; 
 int /*<<< orphan*/  PINDIR_OUTPUT ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_8__*,TYPE_8__**) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_7__*,int) ; 
 int /*<<< orphan*/  basefunc_vtbl ; 
 int /*<<< orphan*/  pin_in_name ; 
 int /*<<< orphan*/  pin_out_name ; 
 int /*<<< orphan*/  samplegrabber_vtbl ; 

HRESULT SampleGrabber_create(IUnknown *pUnkOuter, LPVOID *ppv)
{
    SG_Impl* obj = NULL;
    ISeekingPassThru *passthru;
    HRESULT hr;

    TRACE("(%p,%p)\n", pUnkOuter, ppv);

    obj = CoTaskMemAlloc(sizeof(SG_Impl));
    if (NULL == obj) {
        *ppv = NULL;
        return E_OUTOFMEMORY;
    }
    ZeroMemory(obj, sizeof(SG_Impl));

    BaseFilter_Init(&obj->filter, &IBaseFilter_VTable, &CLSID_SampleGrabber,
            (DWORD_PTR)(__FILE__ ": SG_Impl.csFilter"), &basefunc_vtbl);
    obj->IUnknown_inner.lpVtbl = &samplegrabber_vtbl;
    obj->ISampleGrabber_iface.lpVtbl = &ISampleGrabber_VTable;
    obj->IMemInputPin_iface.lpVtbl = &IMemInputPin_VTable;
    obj->pin_in.IPin_iface.lpVtbl = &IPin_In_VTable;
    obj->pin_in.dir = PINDIR_INPUT;
    obj->pin_in.name = pin_in_name;
    obj->pin_in.sg = obj;
    obj->pin_in.pair = NULL;
    obj->pin_out.IPin_iface.lpVtbl = &IPin_Out_VTable;
    obj->pin_out.dir = PINDIR_OUTPUT;
    obj->pin_out.name = pin_out_name;
    obj->pin_out.sg = obj;
    obj->pin_out.pair = NULL;
    obj->mtype.majortype = GUID_NULL;
    obj->mtype.subtype = MEDIASUBTYPE_None;
    obj->mtype.formattype = FORMAT_None;
    obj->allocator = NULL;
    obj->memOutput = NULL;
    obj->grabberIface = NULL;
    obj->grabberMethod = -1;
    obj->oneShot = OneShot_None;
    obj->bufferLen = -1;
    obj->bufferData = NULL;

    if (pUnkOuter)
        obj->outer_unk = pUnkOuter;
    else
        obj->outer_unk = &obj->IUnknown_inner;

    hr = CoCreateInstance(&CLSID_SeekingPassThru, &obj->IUnknown_inner, CLSCTX_INPROC_SERVER,
                          &IID_IUnknown, (void**)&obj->seekthru_unk);
    if(hr)
        return hr;
    IUnknown_QueryInterface(obj->seekthru_unk, &IID_ISeekingPassThru, (void**)&passthru);
    ISeekingPassThru_Init(passthru, FALSE, &obj->pin_in.IPin_iface);
    ISeekingPassThru_Release(passthru);

    *ppv = &obj->IUnknown_inner;
    return S_OK;
}