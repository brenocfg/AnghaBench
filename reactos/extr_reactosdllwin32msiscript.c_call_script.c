#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_6__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_5__ {int /*<<< orphan*/  IActiveScriptSite_iface; int /*<<< orphan*/ * installer; int /*<<< orphan*/ * session; } ;
typedef  TYPE_1__ MsiActiveScriptSite ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  scalar_t__* LPCWSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  IActiveScriptParse ;
typedef  int /*<<< orphan*/  IActiveScript ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_2__ DISPPARAMS ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 scalar_t__ CLSIDFromProgID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  DISPATCH_METHOD ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  ERROR_INSTALL_FAILURE ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IActiveScriptParse_InitNew (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScriptParse_ParseScriptText (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IActiveScriptParse_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IActiveScriptSite_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_AddNamedItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IActiveScript_GetScriptDispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IActiveScript_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IActiveScript_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_SetScriptSite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_SetScriptState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IDispatch_GetIDsOfNames (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IDispatch_Invoke (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IActiveScript ; 
 int /*<<< orphan*/  IID_IActiveScriptParse ; 
 int /*<<< orphan*/  IID_NULL ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int SCRIPTITEM_GLOBALMEMBERS ; 
 int SCRIPTITEM_ISVISIBLE ; 
 int /*<<< orphan*/  SCRIPTSTATE_CONNECTED ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VT_I4 ; 
 int /*<<< orphan*/  V_I4 (int /*<<< orphan*/ *) ; 
 scalar_t__ VariantChangeType (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 scalar_t__ create_activescriptsite (TYPE_1__**) ; 
 scalar_t__ create_msiserver (int /*<<< orphan*/ *,void**) ; 
 scalar_t__ create_session (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__*) ; 
 int /*<<< orphan*/  map_return_value (int /*<<< orphan*/ ) ; 
 int msidbCustomActionTypeJScript ; 
 int msidbCustomActionTypeVBScript ; 
 int /*<<< orphan*/  szJScript ; 
 int /*<<< orphan*/  szSession ; 
 int /*<<< orphan*/  szVBScript ; 

DWORD call_script(MSIHANDLE hPackage, INT type, LPCWSTR script, LPCWSTR function, LPCWSTR action)
{
    HRESULT hr;
    IActiveScript *pActiveScript = NULL;
    IActiveScriptParse *pActiveScriptParse = NULL;
    MsiActiveScriptSite *scriptsite;
    IDispatch *pDispatch = NULL;
    DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
    DISPID dispid;
    CLSID clsid;
    VARIANT var;
    DWORD ret = ERROR_INSTALL_FAILURE;

    CoInitialize(NULL);

    /* Create MsiActiveScriptSite object */
    hr = create_activescriptsite(&scriptsite);
    if (hr != S_OK) goto done;

    /* Create an installer object */
    hr = create_msiserver(NULL, (void**)&scriptsite->installer);
    if (hr != S_OK) goto done;

    /* Create a session object */
    hr = create_session(hPackage, scriptsite->installer, &scriptsite->session);
    if (hr != S_OK) goto done;

    /* Create the scripting engine */
    type &= msidbCustomActionTypeJScript|msidbCustomActionTypeVBScript;
    if (type == msidbCustomActionTypeJScript)
        hr = CLSIDFromProgID(szJScript, &clsid);
    else if (type == msidbCustomActionTypeVBScript)
        hr = CLSIDFromProgID(szVBScript, &clsid);
    else {
        ERR("Unknown script type %d\n", type);
        goto done;
    }
    if (FAILED(hr)) {
        ERR("Could not find CLSID for Windows Script\n");
        goto done;
    }
    hr = CoCreateInstance(&clsid, NULL, CLSCTX_INPROC_SERVER, &IID_IActiveScript, (void **)&pActiveScript);
    if (FAILED(hr)) {
        ERR("Could not instantiate class for Windows Script\n");
        goto done;
    }

    hr = IActiveScript_QueryInterface(pActiveScript, &IID_IActiveScriptParse, (void **)&pActiveScriptParse);
    if (FAILED(hr)) goto done;

    hr = IActiveScript_SetScriptSite(pActiveScript, &scriptsite->IActiveScriptSite_iface);
    if (FAILED(hr)) goto done;

    hr = IActiveScriptParse_InitNew(pActiveScriptParse);
    if (FAILED(hr)) goto done;

    hr = IActiveScript_AddNamedItem(pActiveScript, szSession, SCRIPTITEM_GLOBALMEMBERS|SCRIPTITEM_ISVISIBLE);
    if (FAILED(hr)) goto done;

    hr = IActiveScriptParse_ParseScriptText(pActiveScriptParse, script, NULL, NULL, NULL, 0, 0, 0L, NULL, NULL);
    if (FAILED(hr)) goto done;

    hr = IActiveScript_SetScriptState(pActiveScript, SCRIPTSTATE_CONNECTED);
    if (FAILED(hr)) goto done;

    /* Call a function if necessary through the IDispatch interface */
    if (function && function[0]) {
        TRACE("Calling function %s\n", debugstr_w(function));

        hr = IActiveScript_GetScriptDispatch(pActiveScript, NULL, &pDispatch);
        if (FAILED(hr)) goto done;

        hr = IDispatch_GetIDsOfNames(pDispatch, &IID_NULL, (WCHAR **)&function, 1,LOCALE_USER_DEFAULT, &dispid);
        if (FAILED(hr)) goto done;

        hr = IDispatch_Invoke(pDispatch, dispid, &IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dispparamsNoArgs, &var, NULL, NULL);
        if (FAILED(hr)) goto done;

        hr = VariantChangeType(&var, &var, 0, VT_I4);
        if (FAILED(hr)) goto done;

        ret = map_return_value(V_I4(&var));

        VariantClear(&var);
    } else {
        /* If no function to be called, MSI behavior is to succeed */
        ret = ERROR_SUCCESS;
    }

done:

    if (pDispatch) IDispatch_Release(pDispatch);
    if (pActiveScript) IActiveScript_Release(pActiveScript);
    if (pActiveScriptParse) IActiveScriptParse_Release(pActiveScriptParse);
    if (scriptsite)
    {
        if (scriptsite->session) IDispatch_Release(scriptsite->session);
        if (scriptsite->installer) IDispatch_Release(scriptsite->installer);
        IActiveScriptSite_Release(&scriptsite->IActiveScriptSite_iface);
    }
    CoUninitialize();    /* must call even if CoInitialize failed */
    return ret;
}