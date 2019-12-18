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
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IActiveScriptParse_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IActiveScriptParse_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IVariantChangeType ; 
 int /*<<< orphan*/  IVariantChangeType_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * create_script () ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  parse_script_a (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  script_change_type ; 
 int /*<<< orphan*/  stored_obj ; 
 int /*<<< orphan*/  testArgConv ; 
 int /*<<< orphan*/  test_change_types (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void run_scripts(void)
{
    IActiveScriptParse *parser;
    HRESULT hres;

    parser = create_script();

    hres = IActiveScriptParse_QueryInterface(parser, &IID_IVariantChangeType, (void**)&script_change_type);
    ok(hres == S_OK, "Could not get IVariantChangeType iface: %08x\n", hres);

    SET_EXPECT(testArgConv);
    parse_script_a(parser,
                   "var obj = {"
                   "    toString: function() { return 'strval'; },"
                   "    valueOf: function()  { return 10; }"
                   "};"
                   "testArgConv(obj);");
    CHECK_CALLED(testArgConv);

    test_change_types(script_change_type, stored_obj);
    IDispatch_Release(stored_obj);
    IVariantChangeType_Release(script_change_type);

    IActiveScriptParse_Release(parser);
}