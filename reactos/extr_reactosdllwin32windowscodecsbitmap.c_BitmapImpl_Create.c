#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WICBitmapCreateCacheOption ;
typedef  int UINT ;
struct TYPE_16__ {TYPE_4__* DebugInfo; } ;
struct TYPE_14__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {int ref; int offset; int width; int height; int stride; int bpp; double dpix; double dpiy; TYPE_5__ IWICBitmap_iface; TYPE_7__ cs; int /*<<< orphan*/  pixelformat; void* view; int /*<<< orphan*/ * data; scalar_t__ lock; scalar_t__ palette_set; int /*<<< orphan*/ * palette; TYPE_3__ IMILUnknown2_iface; TYPE_2__ IMILUnknown1_iface; TYPE_1__ IMILBitmapSource_iface; } ;
struct TYPE_13__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/  REFWICPixelFormatGUID ;
typedef  TYPE_5__ IWICBitmap ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  scalar_t__ DWORD_PTR ;
typedef  TYPE_6__ BitmapImpl ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  BitmapImpl_Vtbl ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  IMILBitmapImpl_Vtbl ; 
 int /*<<< orphan*/  IMILUnknown1Impl_Vtbl ; 
 int /*<<< orphan*/  IMILUnknown2Impl_Vtbl ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_7__*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WINCODEC_ERR_INSUFFICIENTBUFFER ; 
 int /*<<< orphan*/  get_pixelformat_bpp (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

HRESULT BitmapImpl_Create(UINT uiWidth, UINT uiHeight, UINT stride, UINT datasize, void *view,
    UINT offset, REFWICPixelFormatGUID pixelFormat, WICBitmapCreateCacheOption option,
    IWICBitmap **ppIBitmap)
{
    HRESULT hr;
    BitmapImpl *This;
    BYTE *data;
    UINT bpp;

    hr = get_pixelformat_bpp(pixelFormat, &bpp);
    if (FAILED(hr)) return hr;

    if (!stride) stride = (((bpp*uiWidth)+31)/32)*4;
    if (!datasize) datasize = stride * uiHeight;

    if (datasize < stride * uiHeight) return WINCODEC_ERR_INSUFFICIENTBUFFER;
    if (stride < ((bpp*uiWidth)+7)/8) return E_INVALIDARG;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(BitmapImpl));
    if (!This) return E_OUTOFMEMORY;

    if (view) data = (BYTE *)view + offset;
    else if (!(data = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, datasize)))
    {
        HeapFree(GetProcessHeap(), 0, This);
        return E_OUTOFMEMORY;
    }

    This->IWICBitmap_iface.lpVtbl = &BitmapImpl_Vtbl;
    This->IMILBitmapSource_iface.lpVtbl = &IMILBitmapImpl_Vtbl;
    This->IMILUnknown1_iface.lpVtbl = &IMILUnknown1Impl_Vtbl;
    This->IMILUnknown2_iface.lpVtbl = &IMILUnknown2Impl_Vtbl;
    This->ref = 1;
    This->palette = NULL;
    This->palette_set = 0;
    This->lock = 0;
    This->data = data;
    This->view = view;
    This->offset = offset;
    This->width = uiWidth;
    This->height = uiHeight;
    This->stride = stride;
    This->bpp = bpp;
    memcpy(&This->pixelformat, pixelFormat, sizeof(GUID));
    This->dpix = This->dpiy = 0.0;
    InitializeCriticalSection(&This->cs);
    This->cs.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": BitmapImpl.lock");

    *ppIBitmap = &This->IWICBitmap_iface;

    return S_OK;
}