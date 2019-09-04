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
typedef  int /*<<< orphan*/  IHTMLDocument2 ;

/* Variables and functions */
 int /*<<< orphan*/  AddNamedItem ; 
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_CALLED_BROKEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Close ; 
 int /*<<< orphan*/  CreateInstance ; 
 int /*<<< orphan*/  GetInterfaceSafetyOptions ; 
 int /*<<< orphan*/  GetScriptState ; 
 int /*<<< orphan*/  IActiveScriptSite_Release (scalar_t__) ; 
 int /*<<< orphan*/  IDispatchEx_Release (scalar_t__) ; 
 int /*<<< orphan*/  IHTMLDocument2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitNew ; 
 int /*<<< orphan*/  ParseScriptText_script ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetInterfaceSafetyOptions ; 
 int /*<<< orphan*/  SetProperty_ABBREVIATE_GLOBALNAME_RESOLUTION ; 
 int /*<<< orphan*/  SetProperty_HACK_TRIDENTEVENTSINK ; 
 int /*<<< orphan*/  SetProperty_INVOKEVERSIONING ; 
 int /*<<< orphan*/  SetScriptSite ; 
 int /*<<< orphan*/  SetScriptState_CONNECTED ; 
 int /*<<< orphan*/  SetScriptState_DISCONNECTED ; 
 int /*<<< orphan*/  SetScriptState_STARTED ; 
 int /*<<< orphan*/ * create_document () ; 
 int /*<<< orphan*/  load_doc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_script_str ; 
 scalar_t__ site ; 
 int /*<<< orphan*/  test_exec_script (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ window_dispex ; 

__attribute__((used)) static void test_simple_script(void)
{
    IHTMLDocument2 *doc;

    doc = create_document();
    if(!doc)
        return;

    SET_EXPECT(CreateInstance);
    SET_EXPECT(GetInterfaceSafetyOptions);
    SET_EXPECT(SetInterfaceSafetyOptions);
    SET_EXPECT(SetProperty_INVOKEVERSIONING); /* IE8 */
    SET_EXPECT(SetProperty_HACK_TRIDENTEVENTSINK);
    SET_EXPECT(InitNew);
    SET_EXPECT(SetScriptSite);
    SET_EXPECT(GetScriptState);
    SET_EXPECT(SetScriptState_STARTED);
    SET_EXPECT(AddNamedItem);
    SET_EXPECT(SetProperty_ABBREVIATE_GLOBALNAME_RESOLUTION); /* IE8 */
    SET_EXPECT(ParseScriptText_script);
    SET_EXPECT(SetScriptState_CONNECTED);

    load_doc(doc, simple_script_str);

    CHECK_CALLED(CreateInstance);
    CHECK_CALLED(GetInterfaceSafetyOptions);
    CHECK_CALLED(SetInterfaceSafetyOptions);
    CHECK_CALLED_BROKEN(SetProperty_INVOKEVERSIONING); /* IE8 */
    CHECK_CALLED(SetProperty_HACK_TRIDENTEVENTSINK);
    CHECK_CALLED(InitNew);
    CHECK_CALLED(SetScriptSite);
    CHECK_CALLED(GetScriptState);
    CHECK_CALLED(SetScriptState_STARTED);
    CHECK_CALLED(AddNamedItem);
    CHECK_CALLED_BROKEN(SetProperty_ABBREVIATE_GLOBALNAME_RESOLUTION); /* IE8 */
    CHECK_CALLED(ParseScriptText_script);
    CHECK_CALLED(SetScriptState_CONNECTED);

    test_exec_script(doc, "execScript call", "TestScript");

    if(site)
        IActiveScriptSite_Release(site);
    if(window_dispex)
        IDispatchEx_Release(window_dispex);

    SET_EXPECT(SetScriptState_DISCONNECTED);
    SET_EXPECT(Close);

    IHTMLDocument2_Release(doc);

    CHECK_CALLED(SetScriptState_DISCONNECTED);
    CHECK_CALLED(Close);
}