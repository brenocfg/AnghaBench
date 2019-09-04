#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * ppPins; } ;
typedef  TYPE_1__ TestFilterImpl ;
struct TYPE_9__ {int /*<<< orphan*/  achName; int /*<<< orphan*/  pGraph; } ;
struct TYPE_8__ {int /*<<< orphan*/  pFilter; } ;
typedef  TYPE_2__ PIN_INFO ;
typedef  int /*<<< orphan*/  IPin ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_3__ FILTER_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ E_NOTIMPL ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ IBaseFilter_QueryFilterInfo (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  IBaseFilter_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFilterGraph_Release (int /*<<< orphan*/ ) ; 
 scalar_t__ IPin_ConnectedTo (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IPin_QueryPinInfo (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  IPin_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_FILTER_NAME ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static HRESULT get_connected_filter_name(TestFilterImpl *pFilter, char *FilterName)
{
    IPin *pin = NULL;
    PIN_INFO pinInfo;
    FILTER_INFO filterInfo;
    HRESULT hr;

    FilterName[0] = 0;

    hr = IPin_ConnectedTo(pFilter->ppPins[0], &pin);
    ok(hr == S_OK, "IPin_ConnectedTo failed with %x\n", hr);

    hr = IPin_QueryPinInfo(pin, &pinInfo);
    ok(hr == S_OK, "IPin_QueryPinInfo failed with %x\n", hr);
    IPin_Release(pin);

    SetLastError(0xdeadbeef);
    hr = IBaseFilter_QueryFilterInfo(pinInfo.pFilter, &filterInfo);
    if (hr == S_OK && GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
    {
        IBaseFilter_Release(pinInfo.pFilter);
        return E_NOTIMPL;
    }
    ok(hr == S_OK, "IBaseFilter_QueryFilterInfo failed with %x\n", hr);
    IBaseFilter_Release(pinInfo.pFilter);

    IFilterGraph_Release(filterInfo.pGraph);

    WideCharToMultiByte(CP_ACP, 0, filterInfo.achName, -1, FilterName, MAX_FILTER_NAME, NULL, NULL);

    return S_OK;
}