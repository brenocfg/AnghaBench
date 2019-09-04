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
typedef  int /*<<< orphan*/  IActiveScriptParse ;
typedef  int /*<<< orphan*/  IActiveScript ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ActiveScriptSite ; 
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IActiveScriptParse_InitNew (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScriptParse_ParseScriptText (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IActiveScriptParse_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_AddNamedItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IActiveScript_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IActiveScript_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_SetScriptSite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_SetScriptState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IActiveScriptParse ; 
 int SCRIPTITEM_GLOBALMEMBERS ; 
 int SCRIPTITEM_ISSOURCE ; 
 int SCRIPTITEM_ISVISIBLE ; 
 int /*<<< orphan*/  SCRIPTSTATE_STARTED ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a2bstr (char*) ; 
 int /*<<< orphan*/ * create_script () ; 
 int /*<<< orphan*/  global_success_d ; 
 int /*<<< orphan*/  global_success_i ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/ * script_engine ; 
 int /*<<< orphan*/  testW ; 

__attribute__((used)) static void test_start(void)
{
    IActiveScriptParse *parser;
    IActiveScript *engine;
    BSTR str;
    HRESULT hres;

    script_engine = engine = create_script();
    if(!engine)
        return;

    hres = IActiveScript_QueryInterface(engine, &IID_IActiveScriptParse, (void**)&parser);
    ok(hres == S_OK, "Could not get IActiveScriptParse: %08x\n", hres);

    hres = IActiveScriptParse_InitNew(parser);
    ok(hres == S_OK, "InitNew failed: %08x\n", hres);

    hres = IActiveScript_SetScriptSite(engine, &ActiveScriptSite);
    ok(hres == S_OK, "SetScriptSite failed: %08x\n", hres);

    hres = IActiveScript_AddNamedItem(engine, testW, SCRIPTITEM_ISVISIBLE|SCRIPTITEM_ISSOURCE|SCRIPTITEM_GLOBALMEMBERS);
    ok(hres == S_OK, "AddNamedItem failed: %08x\n", hres);

    str = a2bstr("ok(getScriptState() === 5, \"getScriptState = \" + getScriptState());\n"
                 "reportSuccess();");
    hres = IActiveScriptParse_ParseScriptText(parser, str, NULL, NULL, NULL, 0, 0, 0, NULL, NULL);
    ok(hres == S_OK, "ParseScriptText failed: %08x\n", hres);
    SysFreeString(str);

    SET_EXPECT(global_success_d);
    SET_EXPECT(global_success_i);
    hres = IActiveScript_SetScriptState(engine, SCRIPTSTATE_STARTED);
    ok(hres == S_OK, "SetScriptState(SCRIPTSTATE_STARTED) failed: %08x\n", hres);
    CHECK_CALLED(global_success_d);
    CHECK_CALLED(global_success_i);

    IActiveScript_Release(engine);
    IActiveScriptParse_Release(parser);
    script_engine = NULL;
}