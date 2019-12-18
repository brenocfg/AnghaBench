#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_6__ {int /*<<< orphan*/  it; } ;
typedef  TYPE_2__ aout_sys_t ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IMMDevice ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DeviceHotplugReport (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeviceIsRender (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMMDeviceEnumerator_GetDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IMMDevice_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT DeviceUpdated(audio_output_t *aout, LPCWSTR wid)
{
    aout_sys_t *sys = aout->sys;
    HRESULT hr;

    IMMDevice *dev;
    hr = IMMDeviceEnumerator_GetDevice(sys->it, wid, &dev);
    if (FAILED(hr))
        return hr;

    if (!DeviceIsRender(dev))
    {
        IMMDevice_Release(dev);
        return S_OK;
    }

    DeviceHotplugReport(aout, wid, dev);
    IMMDevice_Release(dev);
    return S_OK;
}