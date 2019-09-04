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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IDispatchEx ;
typedef  int /*<<< orphan*/  IActiveScriptParse ;
typedef  int /*<<< orphan*/  IActiveScript ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ActiveScriptSite ; 
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 scalar_t__ E_POINTER ; 
 scalar_t__ E_UNEXPECTED ; 
 int /*<<< orphan*/  GetLCID ; 
 scalar_t__ IActiveScriptParse_InitNew (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IActiveScriptParse_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_Close (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IActiveScript_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_SetScriptSite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_SetScriptState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDispatchEx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IActiveScriptParse ; 
 int /*<<< orphan*/  OnStateChange_CLOSED ; 
 int /*<<< orphan*/  OnStateChange_INITIALIZED ; 
 int /*<<< orphan*/  OnStateChange_STARTED ; 
 int /*<<< orphan*/  SCRIPTSTATE_CLOSED ; 
 int /*<<< orphan*/  SCRIPTSTATE_INITIALIZED ; 
 int /*<<< orphan*/  SCRIPTSTATE_STARTED ; 
 int /*<<< orphan*/  SCRIPTSTATE_UNINITIALIZED ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * create_jscript () ; 
 int /*<<< orphan*/ * get_script_dispatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_invoke_versioning (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_no_script_dispatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_safety (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_script_dispatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_jscript(void)
{
    IActiveScriptParse *parse;
    IActiveScript *script;
    IDispatchEx *dispex;
    ULONG ref;
    HRESULT hres;

    script = create_jscript();

    hres = IActiveScript_QueryInterface(script, &IID_IActiveScriptParse, (void**)&parse);
    ok(hres == S_OK, "Could not get IActiveScriptParse: %08x\n", hres);

    test_state(script, SCRIPTSTATE_UNINITIALIZED);
    test_safety((IUnknown*)script);
    test_invoke_versioning(script);

    hres = IActiveScriptParse_InitNew(parse);
    ok(hres == S_OK, "InitNew failed: %08x\n", hres);

    hres = IActiveScriptParse_InitNew(parse);
    ok(hres == E_UNEXPECTED, "InitNew failed: %08x, expected E_UNEXPECTED\n", hres);

    hres = IActiveScript_SetScriptSite(script, NULL);
    ok(hres == E_POINTER, "SetScriptSite failed: %08x, expected E_POINTER\n", hres);

    test_state(script, SCRIPTSTATE_UNINITIALIZED);
    test_no_script_dispatch(script);

    SET_EXPECT(GetLCID);
    SET_EXPECT(OnStateChange_INITIALIZED);
    hres = IActiveScript_SetScriptSite(script, &ActiveScriptSite);
    ok(hres == S_OK, "SetScriptSite failed: %08x\n", hres);
    CHECK_CALLED(GetLCID);
    CHECK_CALLED(OnStateChange_INITIALIZED);

    test_state(script, SCRIPTSTATE_INITIALIZED);

    hres = IActiveScript_SetScriptSite(script, &ActiveScriptSite);
    ok(hres == E_UNEXPECTED, "SetScriptSite failed: %08x, expected E_UNEXPECTED\n", hres);

    dispex = get_script_dispatch(script);
    test_script_dispatch(dispex);

    SET_EXPECT(OnStateChange_STARTED);
    hres = IActiveScript_SetScriptState(script, SCRIPTSTATE_STARTED);
    ok(hres == S_OK, "SetScriptState(SCRIPTSTATE_STARTED) failed: %08x\n", hres);
    CHECK_CALLED(OnStateChange_STARTED);

    test_state(script, SCRIPTSTATE_STARTED);

    SET_EXPECT(OnStateChange_CLOSED);
    hres = IActiveScript_Close(script);
    ok(hres == S_OK, "Close failed: %08x\n", hres);
    CHECK_CALLED(OnStateChange_CLOSED);

    test_state(script, SCRIPTSTATE_CLOSED);
    test_no_script_dispatch(script);
    test_script_dispatch(dispex);
    IDispatchEx_Release(dispex);

    IActiveScriptParse_Release(parse);

    ref = IActiveScript_Release(script);
    ok(!ref, "ref = %d\n", ref);
}