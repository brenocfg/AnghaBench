#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  IFilterMapper_iface; } ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ FilterMapper3Impl ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FilterMapper2_create (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

HRESULT FilterMapper_create(IUnknown *pUnkOuter, LPVOID *ppObj)
{
    FilterMapper3Impl *pFM2impl;
    HRESULT hr;

    TRACE("(%p, %p)\n", pUnkOuter, ppObj);

    hr = FilterMapper2_create(pUnkOuter, (LPVOID*)&pFM2impl);
    if (FAILED(hr))
        return hr;

    *ppObj = &pFM2impl->IFilterMapper_iface;

    return hr;
}