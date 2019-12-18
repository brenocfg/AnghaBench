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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  IActiveScriptParse ;
typedef  int /*<<< orphan*/  IActiveScript ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ IActiveScriptParse_ParseScriptText (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IActiveScriptParse_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IActiveScriptParse ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a2bstr (char*) ; 
 int /*<<< orphan*/  close_script (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_and_init_script (int /*<<< orphan*/ ) ; 
 int global_ref ; 
 int /*<<< orphan*/  global_success_d ; 
 int /*<<< orphan*/  global_success_i ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 char const* testW ; 

__attribute__((used)) static void test_parse_context(void)
{
    IActiveScriptParse *parser;
    IActiveScript *engine;
    BSTR str;
    HRESULT hres;

    static const WCHAR xW[] = {'x',0};
    static const WCHAR yW[] = {'y',0};

    global_ref = 1;
    engine = create_and_init_script(0);
    if(!engine)
        return;

    hres = IActiveScript_QueryInterface(engine, &IID_IActiveScriptParse, (void**)&parser);
    ok(hres == S_OK, "Could not get IActiveScriptParse: %08x\n", hres);

    /* unknown identifier context is not a valid argument */
    str = a2bstr("Call reportSuccess()\n");
    hres = IActiveScriptParse_ParseScriptText(parser, str, yW, NULL, NULL, 0, 0, 0, NULL, NULL);
    ok(hres == E_INVALIDARG, "ParseScriptText failed: %08x\n", hres);
    SysFreeString(str);

    str = a2bstr("class Cl\n"
                 "    Public Sub ClMethod\n"
                 "        Call reportSuccess()\n"
                 "    End Sub\n"
                 "End Class\n"
                 "Dim x\n"
                 "set x = new Cl\n");
    hres = IActiveScriptParse_ParseScriptText(parser, str, NULL, NULL, NULL, 0, 0, 0, NULL, NULL);
    ok(hres == S_OK, "ParseScriptText failed: %08x\n", hres);
    SysFreeString(str);

    /* known global variable is not a valid context */
    str = a2bstr("Call reportSuccess()\n");
    hres = IActiveScriptParse_ParseScriptText(parser, str, xW, NULL, NULL, 0, 0, 0, NULL, NULL);
    ok(hres == E_INVALIDARG, "ParseScriptText failed: %08x\n", hres);
    SysFreeString(str);

    SET_EXPECT(global_success_d);
    SET_EXPECT(global_success_i);
    str = a2bstr("Call reportSuccess()\n");
    hres = IActiveScriptParse_ParseScriptText(parser, str, testW, NULL, NULL, 0, 0, 0, NULL, NULL);
    ok(hres == S_OK, "ParseScriptText failed: %08x\n", hres);
    SysFreeString(str);
    CHECK_CALLED(global_success_d);
    CHECK_CALLED(global_success_i);

    IActiveScriptParse_Release(parser);
    close_script(engine);
    ok(global_ref == 1, "global_ref = %u\n", global_ref);
}