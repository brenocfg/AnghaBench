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
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  IActiveScriptParse ;
typedef  int /*<<< orphan*/  IActiveScript ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ActiveScriptSite ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IActiveScriptParse_InitNew (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScriptParse_ParseScriptText (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScriptParse_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_AddNamedItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IActiveScript_Close (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IActiveScript_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_SetScriptSite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_SetScriptState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IActiveScriptParse ; 
 int SCRIPTITEM_GLOBALMEMBERS ; 
 int SCRIPTITEM_ISSOURCE ; 
 int SCRIPTITEM_ISVISIBLE ; 
 int /*<<< orphan*/  SCRIPTSTATE_STARTED ; 
 int /*<<< orphan*/  SCRIPTSTATE_UNINITIALIZED ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a2bstr (char*) ; 
 int /*<<< orphan*/ * create_script () ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ refobj_ref ; 
 int /*<<< orphan*/  testW ; 

__attribute__((used)) static HRESULT test_global_vars_ref(BOOL use_close)
{
    IActiveScriptParse *parser;
    IActiveScript *engine;
    BSTR script_str;
    LONG ref;
    HRESULT hres;

    engine = create_script();
    if(!engine)
        return S_OK;

    hres = IActiveScript_QueryInterface(engine, &IID_IActiveScriptParse, (void**)&parser);
    ok(hres == S_OK, "Could not get IActiveScriptParse: %08x\n", hres);
    if (FAILED(hres))
    {
        IActiveScript_Release(engine);
        return hres;
    }

    hres = IActiveScriptParse_InitNew(parser);
    ok(hres == S_OK, "InitNew failed: %08x\n", hres);

    hres = IActiveScript_SetScriptSite(engine, &ActiveScriptSite);
    ok(hres == S_OK, "SetScriptSite failed: %08x\n", hres);

    hres = IActiveScript_AddNamedItem(engine, testW, SCRIPTITEM_ISVISIBLE|SCRIPTITEM_ISSOURCE|SCRIPTITEM_GLOBALMEMBERS);
    ok(hres == S_OK, "AddNamedItem failed: %08x\n", hres);

    hres = IActiveScript_SetScriptState(engine, SCRIPTSTATE_STARTED);
    ok(hres == S_OK, "SetScriptState(SCRIPTSTATE_STARTED) failed: %08x\n", hres);

    refobj_ref = 0;

    script_str = a2bstr("Dim x\nset x = RefObj\n");
    hres = IActiveScriptParse_ParseScriptText(parser, script_str, NULL, NULL, NULL, 0, 0, 0, NULL, NULL);
    SysFreeString(script_str);

    ok(refobj_ref, "refobj_ref = 0\n");

    if(use_close) {
        hres = IActiveScript_Close(engine);
        ok(hres == S_OK, "Close failed: %08x\n", hres);
    }else {
        hres = IActiveScript_SetScriptState(engine, SCRIPTSTATE_UNINITIALIZED);
        ok(hres == S_OK, "SetScriptState(SCRIPTSTATE_STARTED) failed: %08x\n", hres);
    }

    ok(!refobj_ref, "refobj_ref = %d\n", refobj_ref);

    IActiveScript_Release(engine);

    ref = IActiveScriptParse_Release(parser);
    ok(!ref, "ref=%d\n", ref);
    return hres;
}