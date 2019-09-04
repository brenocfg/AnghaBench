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
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  IActiveScriptProperty ;
typedef  int /*<<< orphan*/  IActiveScript ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  IActiveScriptProperty_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScriptProperty_SetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IActiveScriptProperty ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static HRESULT set_script_prop(IActiveScript *engine, DWORD property, VARIANT *val)
{
    IActiveScriptProperty *script_prop;
    HRESULT hres;

    hres = IActiveScript_QueryInterface(engine, &IID_IActiveScriptProperty,
            (void**)&script_prop);
    ok(hres == S_OK, "Could not get IActiveScriptProperty iface: %08x\n", hres);

    hres = IActiveScriptProperty_SetProperty(script_prop, property, NULL, val);
    IActiveScriptProperty_Release(script_prop);

    return hres;
}