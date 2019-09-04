#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransformFilterFuncTable ;
struct TYPE_7__ {int /*<<< orphan*/  IBaseFilter_iface; } ;
struct TYPE_8__ {TYPE_1__ filter; } ;
typedef  TYPE_2__ TransformFilter ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  IBaseFilterVtbl ;
typedef  int /*<<< orphan*/  IBaseFilter ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 TYPE_2__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  CoTaskMemFree (TYPE_2__*) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TransformFilter_Init (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_2__*) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 

HRESULT TransformFilter_Construct(const IBaseFilterVtbl *pVtbl, LONG filter_size, const CLSID* pClsid, const TransformFilterFuncTable* pFuncsTable, IBaseFilter ** ppTransformFilter)
{
    TransformFilter* pTf;

    *ppTransformFilter = NULL;

    assert(filter_size >= sizeof(TransformFilter));

    pTf = CoTaskMemAlloc(filter_size);

    if (!pTf)
        return E_OUTOFMEMORY;

    ZeroMemory(pTf, filter_size);

    if (SUCCEEDED(TransformFilter_Init(pVtbl, pClsid, pFuncsTable, pTf)))
    {
        *ppTransformFilter = &pTf->filter.IBaseFilter_iface;
        return S_OK;
    }

    CoTaskMemFree(pTf);
    return E_FAIL;
}