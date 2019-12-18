#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  IMMEndpoint ;
typedef  int /*<<< orphan*/  IMMDevice ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ EDataFlow ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ DEVICE_STATE_ACTIVE ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IMMEndpoint ; 
 int /*<<< orphan*/  IMMDevice_GetState (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IMMDevice_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMMEndpoint_GetDataFlow (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IMMEndpoint_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ eRender ; 

__attribute__((used)) static bool DeviceIsRender(IMMDevice *dev)
{
    void *pv;

    if (FAILED(IMMDevice_QueryInterface(dev, &IID_IMMEndpoint, &pv)))
        return false;

    IMMEndpoint *ep = pv;
    EDataFlow flow;
    HRESULT hr = IMMEndpoint_GetDataFlow(ep, &flow);

    IMMEndpoint_Release(ep);
    if (FAILED(hr) || flow != eRender)
        return false;

    DWORD pdwState;
    hr = IMMDevice_GetState(dev, &pdwState);
    return !FAILED(hr) && pdwState == DEVICE_STATE_ACTIVE;
}