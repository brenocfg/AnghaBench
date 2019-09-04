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
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ActiveScriptSite ; 
 scalar_t__ IActiveScriptParse_InitNew (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IActiveScriptParse_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_AddNamedItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IActiveScript_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IActiveScript_SetScriptSite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_SetScriptState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IActiveScriptParse ; 
 int SCRIPTITEM_ISSOURCE ; 
 int SCRIPTITEM_ISVISIBLE ; 
 int /*<<< orphan*/  SCRIPTSTATE_STARTED ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * create_script () ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  testW ; 

__attribute__((used)) static IActiveScript *create_and_init_script(DWORD flags)
{
    IActiveScriptParse *parser;
    IActiveScript *engine;
    HRESULT hres;

    engine = create_script();
    if(!engine)
        return NULL;

    hres = IActiveScript_QueryInterface(engine, &IID_IActiveScriptParse, (void**)&parser);
    ok(hres == S_OK, "Could not get IActiveScriptParse: %08x\n", hres);

    hres = IActiveScriptParse_InitNew(parser);
    ok(hres == S_OK, "InitNew failed: %08x\n", hres);

    IActiveScriptParse_Release(parser);

    hres = IActiveScript_SetScriptSite(engine, &ActiveScriptSite);
    ok(hres == S_OK, "SetScriptSite failed: %08x\n", hres);

    hres = IActiveScript_AddNamedItem(engine, testW,
            SCRIPTITEM_ISVISIBLE|SCRIPTITEM_ISSOURCE|flags);
    ok(hres == S_OK, "AddNamedItem failed: %08x\n", hres);

    hres = IActiveScript_SetScriptState(engine, SCRIPTSTATE_STARTED);
    ok(hres == S_OK, "SetScriptState(SCRIPTSTATE_STARTED) failed: %08x\n", hres);

    return engine;
}