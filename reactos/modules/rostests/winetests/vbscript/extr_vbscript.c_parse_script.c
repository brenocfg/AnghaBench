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
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IActiveScriptParse_ParseScriptText (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OnEnterScript ; 
 int /*<<< orphan*/  OnLeaveScript ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a2bstr (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void parse_script(IActiveScriptParse *parse, const char *src)
{
    BSTR str;
    HRESULT hres;

    SET_EXPECT(OnEnterScript);
    SET_EXPECT(OnLeaveScript);

    str = a2bstr(src);
    hres = IActiveScriptParse_ParseScriptText(parse, str, NULL, NULL, NULL, 0, 0, 0, NULL, NULL);
    SysFreeString(str);
    ok(hres == S_OK, "ParseScriptText failed: %08x\n", hres);

    CHECK_CALLED(OnEnterScript);
    CHECK_CALLED(OnLeaveScript);
}