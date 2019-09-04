#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int /*<<< orphan*/ * pmt; int /*<<< orphan*/ * pszFileName; int /*<<< orphan*/ * pOutputPin; TYPE_2__ IAMFilterMiscFlags_iface; TYPE_1__ IFileSourceFilter_iface; int /*<<< orphan*/  filter; } ;
typedef  TYPE_3__* LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  TYPE_3__ AsyncReader ;

/* Variables and functions */
 int /*<<< orphan*/  AsyncReader_Vtbl ; 
 int /*<<< orphan*/  BaseFilter_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BaseFuncTable ; 
 int /*<<< orphan*/  CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  CLSID_AsyncReader ; 
 TYPE_3__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FileSource_Vtbl ; 
 int /*<<< orphan*/  IAMFilterMiscFlags_Vtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*) ; 

HRESULT AsyncReader_create(IUnknown * pUnkOuter, LPVOID * ppv)
{
    AsyncReader *pAsyncRead;
    
    if( pUnkOuter )
        return CLASS_E_NOAGGREGATION;
    
    pAsyncRead = CoTaskMemAlloc(sizeof(AsyncReader));

    if (!pAsyncRead)
        return E_OUTOFMEMORY;

    BaseFilter_Init(&pAsyncRead->filter, &AsyncReader_Vtbl, &CLSID_AsyncReader, (DWORD_PTR)(__FILE__ ": AsyncReader.csFilter"), &BaseFuncTable);

    pAsyncRead->IFileSourceFilter_iface.lpVtbl = &FileSource_Vtbl;
    pAsyncRead->IAMFilterMiscFlags_iface.lpVtbl = &IAMFilterMiscFlags_Vtbl;
    pAsyncRead->pOutputPin = NULL;

    pAsyncRead->pszFileName = NULL;
    pAsyncRead->pmt = NULL;

    *ppv = pAsyncRead;

    TRACE("-- created at %p\n", pAsyncRead);

    return S_OK;
}