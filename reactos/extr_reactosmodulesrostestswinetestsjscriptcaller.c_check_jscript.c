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
typedef  int /*<<< orphan*/  IActiveScriptProperty ;
typedef  int /*<<< orphan*/  IActiveScriptParse ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ IActiveScriptParse_ParseScriptText (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScriptParse_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IActiveScriptParse_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IActiveScriptProperty_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IActiveScriptProperty ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a2bstr (char*) ; 
 int /*<<< orphan*/ * create_script () ; 

__attribute__((used)) static BOOL check_jscript(void)
{
    IActiveScriptProperty *script_prop;
    IActiveScriptParse *parser;
    BSTR str;
    HRESULT hres;

    parser = create_script();
    if(!parser)
        return FALSE;

    str = a2bstr("if(!('localeCompare' in String.prototype)) throw 1;");
    hres = IActiveScriptParse_ParseScriptText(parser, str, NULL, NULL, NULL, 0, 0, 0, NULL, NULL);
    SysFreeString(str);

    if(hres == S_OK)
        hres = IActiveScriptParse_QueryInterface(parser, &IID_IActiveScriptProperty, (void**)&script_prop);
    IActiveScriptParse_Release(parser);
    if(hres == S_OK)
        IActiveScriptProperty_Release(script_prop);

    return hres == S_OK;
}