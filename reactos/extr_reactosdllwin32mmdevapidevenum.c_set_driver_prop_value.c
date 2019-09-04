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
struct TYPE_2__ {int /*<<< orphan*/  (* pGetPropValue ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  PROPVARIANT ;
typedef  int /*<<< orphan*/  PROPERTYKEY ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  EDataFlow ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  MMDevice_SetPropValue (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PropVariantClear (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 TYPE_1__ drvs ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT set_driver_prop_value(GUID *id, const EDataFlow flow, const PROPERTYKEY *prop)
{
    HRESULT hr;
    PROPVARIANT pv;

    if (!drvs.pGetPropValue)
        return E_NOTIMPL;

    hr = drvs.pGetPropValue(id, prop, &pv);

    if (SUCCEEDED(hr))
    {
        MMDevice_SetPropValue(id, flow, prop, &pv);
        PropVariantClear(&pv);
    }

    return hr;
}