#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pwszVal; } ;
typedef  TYPE_1__ PROPVARIANT ;
typedef  int /*<<< orphan*/  IPropertyStore ;
typedef  int /*<<< orphan*/  IMMDevice ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 char* FromWide (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMMDevice_OpenPropertyStore (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IPropertyStore_GetValue (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  IPropertyStore_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PKEY_Device_FriendlyName ; 
 int /*<<< orphan*/  PropVariantClear (TYPE_1__*) ; 
 int /*<<< orphan*/  PropVariantInit (TYPE_1__*) ; 
 int /*<<< orphan*/  STGM_READ ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *DeviceGetFriendlyName(IMMDevice *dev)
{
    IPropertyStore *props;
    PROPVARIANT v;
    HRESULT hr;

    hr = IMMDevice_OpenPropertyStore(dev, STGM_READ, &props);
    if (FAILED(hr))
        return NULL;

    char *name = NULL;
    PropVariantInit(&v);
    hr = IPropertyStore_GetValue(props, &PKEY_Device_FriendlyName, &v);
    if (SUCCEEDED(hr))
    {
        name = FromWide(v.pwszVal);
        PropVariantClear(&v);
    }

    IPropertyStore_Release(props);

    return name;
}