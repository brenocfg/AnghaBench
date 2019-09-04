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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t UINT ;
struct TYPE_2__ {int /*<<< orphan*/  (* pGetEndpointIDs ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int /*<<< orphan*/ ***,size_t*,size_t*) ;} ;
typedef  int /*<<< orphan*/  MMDevice ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * GUID ;
typedef  int /*<<< orphan*/  EDataFlow ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_ACTIVE ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * MMDevice_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_1__ drvs ; 
 int /*<<< orphan*/  set_format (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int /*<<< orphan*/ ***,size_t*,size_t*) ; 

__attribute__((used)) static HRESULT load_driver_devices(EDataFlow flow)
{
    WCHAR **ids;
    GUID *guids;
    UINT num, def, i;
    HRESULT hr;

    if(!drvs.pGetEndpointIDs)
        return S_OK;

    hr = drvs.pGetEndpointIDs(flow, &ids, &guids, &num, &def);
    if(FAILED(hr))
        return hr;

    for(i = 0; i < num; ++i){
        MMDevice *dev;
        dev = MMDevice_Create(ids[i], &guids[i], flow, DEVICE_STATE_ACTIVE,
                def == i);
        set_format(dev);
    }

    HeapFree(GetProcessHeap(), 0, guids);
    HeapFree(GetProcessHeap(), 0, ids);

    return S_OK;
}