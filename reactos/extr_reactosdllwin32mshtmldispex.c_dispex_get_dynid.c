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
typedef  int /*<<< orphan*/  dynamic_prop_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {TYPE_1__* dynamic_data; } ;
struct TYPE_5__ {int /*<<< orphan*/ * props; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ DispatchEx ;
typedef  int DISPID ;

/* Variables and functions */
 int DISPID_DYNPROP_0 ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  fdexNameEnsure ; 
 int /*<<< orphan*/  get_dynamic_prop (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

HRESULT dispex_get_dynid(DispatchEx *This, const WCHAR *name, DISPID *id)
{
    dynamic_prop_t *prop;
    HRESULT hres;

    hres = get_dynamic_prop(This, name, fdexNameEnsure, &prop);
    if(FAILED(hres))
        return hres;

    *id = DISPID_DYNPROP_0 + (prop - This->dynamic_data->props);
    return S_OK;
}