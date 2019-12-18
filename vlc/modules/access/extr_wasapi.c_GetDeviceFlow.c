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
typedef  int EDataFlow ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IMMEndpoint ; 
 int /*<<< orphan*/  IMMDevice_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMMEndpoint_GetDataFlow (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IMMEndpoint_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int eAll ; 

__attribute__((used)) static EDataFlow GetDeviceFlow(IMMDevice *dev)
{
    void *pv;

    if (FAILED(IMMDevice_QueryInterface(dev, &IID_IMMEndpoint, &pv)))
        return false;

    IMMEndpoint *ep = pv;
    EDataFlow flow;

    if (SUCCEEDED(IMMEndpoint_GetDataFlow(ep, &flow)))
        flow = eAll;
    IMMEndpoint_Release(ep);
    return flow;
}