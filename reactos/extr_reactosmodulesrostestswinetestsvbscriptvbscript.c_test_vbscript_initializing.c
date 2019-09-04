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
typedef  int /*<<< orphan*/  IActiveScriptParse ;
typedef  int /*<<< orphan*/  IActiveScript ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ActiveScriptSite ; 
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 scalar_t__ E_UNEXPECTED ; 
 int /*<<< orphan*/  GetLCID ; 
 scalar_t__ IActiveScriptParse_InitNew (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IActiveScriptParse_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_Close (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IActiveScript_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_SetScriptSite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IActiveScriptParse ; 
 int /*<<< orphan*/  OnStateChange_CLOSED ; 
 int /*<<< orphan*/  OnStateChange_INITIALIZED ; 
 int /*<<< orphan*/  SCRIPTSTATE_CLOSED ; 
 int /*<<< orphan*/  SCRIPTSTATE_UNINITIALIZED ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * create_vbscript () ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_vbscript_initializing(void)
{
    IActiveScriptParse *parse;
    IActiveScript *script;
    ULONG ref;
    HRESULT hres;

    script = create_vbscript();

    hres = IActiveScript_QueryInterface(script, &IID_IActiveScriptParse, (void**)&parse);
    ok(hres == S_OK, "Could not get IActiveScriptParse: %08x\n", hres);

    test_state(script, SCRIPTSTATE_UNINITIALIZED);

    SET_EXPECT(GetLCID);
    hres = IActiveScript_SetScriptSite(script, &ActiveScriptSite);
    ok(hres == S_OK, "SetScriptSite failed: %08x\n", hres);
    CHECK_CALLED(GetLCID);

    SET_EXPECT(OnStateChange_INITIALIZED);
    hres = IActiveScriptParse_InitNew(parse);
    ok(hres == S_OK, "InitNew failed: %08x\n", hres);
    CHECK_CALLED(OnStateChange_INITIALIZED);

    hres = IActiveScript_SetScriptSite(script, &ActiveScriptSite);
    ok(hres == E_UNEXPECTED, "SetScriptSite failed: %08x, expected E_UNEXPECTED\n", hres);

    SET_EXPECT(OnStateChange_CLOSED);
    hres = IActiveScript_Close(script);
    ok(hres == S_OK, "Close failed: %08x\n", hres);
    CHECK_CALLED(OnStateChange_CLOSED);

    test_state(script, SCRIPTSTATE_CLOSED);

    IActiveScriptParse_Release(parse);

    ref = IActiveScript_Release(script);
    ok(!ref, "ref = %d\n", ref);
}