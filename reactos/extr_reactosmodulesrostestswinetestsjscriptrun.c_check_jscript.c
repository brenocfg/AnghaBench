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
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int CLSCTX_INPROC_HANDLER ; 
 int CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_JScript ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int FALSE ; 
 int /*<<< orphan*/  IActiveScriptProperty_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IActiveScriptProperty ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a2bstr (char*) ; 
 scalar_t__ parse_script (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL check_jscript(void)
{
    IActiveScriptProperty *script_prop;
    BSTR str;
    HRESULT hres;

    hres = CoCreateInstance(&CLSID_JScript, NULL, CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER,
            &IID_IActiveScriptProperty, (void**)&script_prop);
    if(FAILED(hres))
        return FALSE;
    IActiveScriptProperty_Release(script_prop);

    str = a2bstr("if(!('localeCompare' in String.prototype)) throw 1;");
    hres = parse_script(0, str);
    SysFreeString(str);

    return hres == S_OK;
}