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
typedef  int /*<<< orphan*/  IDispatchEx ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  IActiveScript ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IActiveScript_GetScriptDispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IDispatch_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDispatchEx ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static IDispatchEx *get_script_dispatch(IActiveScript *script)
{
    IDispatchEx *dispex;
    IDispatch *disp;
    HRESULT hres;

    disp = (void*)0xdeadbeef;
    hres = IActiveScript_GetScriptDispatch(script, NULL, &disp);
    ok(hres == S_OK, "GetScriptDispatch failed: %08x\n", hres);

    hres = IDispatch_QueryInterface(disp, &IID_IDispatchEx, (void**)&dispex);
    IDispatch_Release(disp);
    ok(hres == S_OK, "Could not get IDispatch iface: %08x\n", hres);
    return dispex;
}