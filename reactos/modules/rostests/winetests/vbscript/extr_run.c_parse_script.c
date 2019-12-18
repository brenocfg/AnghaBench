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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  IActiveScriptParse ;
typedef  int /*<<< orphan*/  IActiveScript ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  Global ; 
 scalar_t__ IActiveScriptParse_ParseScriptText (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScriptParse_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IActiveScript_Close (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_GetScriptDispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IActiveScript_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IActiveScript_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IActiveScriptParse ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * create_and_init_script (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ test_counter ; 

__attribute__((used)) static HRESULT parse_script(DWORD flags, BSTR script_str, const WCHAR *delim)
{
    IActiveScriptParse *parser;
    IActiveScript *engine;
    IDispatch *script_disp;
    LONG ref;
    HRESULT hres;

    engine = create_and_init_script(flags);
    if(!engine)
        return S_OK;

    hres = IActiveScript_QueryInterface(engine, &IID_IActiveScriptParse, (void**)&parser);
    ok(hres == S_OK, "Could not get IActiveScriptParse: %08x\n", hres);
    if (FAILED(hres))
    {
        IActiveScript_Release(engine);
        return hres;
    }

    hres = IActiveScript_GetScriptDispatch(engine, NULL, &script_disp);
    ok(hres == S_OK, "GetScriptDispatch failed: %08x\n", hres);
    ok(script_disp != NULL, "script_disp == NULL\n");
    ok(script_disp != (IDispatch*)&Global, "script_disp == Global\n");

    test_counter = 0;

    hres = IActiveScriptParse_ParseScriptText(parser, script_str, NULL, NULL, delim, 0, 0, 0, NULL, NULL);

    IActiveScript_Close(engine);

    IDispatch_Release(script_disp);
    IActiveScript_Release(engine);

    ref = IActiveScriptParse_Release(parser);
    ok(!ref, "ref=%d\n", ref);
    return hres;
}