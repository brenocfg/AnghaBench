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
typedef  int /*<<< orphan*/  wszCLSIDInstance ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  REFCLSID ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  IPropertyBag ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int CHARS_IN_GUID ; 
 int /*<<< orphan*/  CLASS_E_CLASSNOTAVAILABLE ; 
 int /*<<< orphan*/  CLSIDFromString (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  IID_IPropertyBag ; 
 int /*<<< orphan*/  IPropertyBag_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstanceObjectFactory_Constructor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  RegistryPropertyBag_Constructor (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 

HRESULT SHDOCVW_GetShellInstanceObjectClassObject(REFCLSID rclsid, REFIID riid, 
    LPVOID *ppvClassObj)
{
    WCHAR wszInstanceKey[] = { 'C','L','S','I','D','\\','{','0','0','0','0','0','0','0','0','-',
        '0','0','0','0','-','0','0','0','0','-','0','0','0','0','-','0','0','0','0','0','0','0','0',
        '0','0','0','0','}','\\','I','n','s','t','a','n','c','e', 0 };
    static const WCHAR wszCLSID[] = { 'C','L','S','I','D',0 };
    static const WCHAR wszInitPropertyBag[] =
        { 'I','n','i','t','P','r','o','p','e','r','t','y','B','a','g',0 };
    WCHAR wszCLSIDInstance[CHARS_IN_GUID];
    CLSID clsidInstance;
    HKEY hInstanceKey, hInitPropertyBagKey;
    DWORD dwType, cbBytes = sizeof(wszCLSIDInstance);
    IPropertyBag *pInitPropertyBag;
    HRESULT hr;
    LONG res;
        
    TRACE("(rclsid=%s, riid=%s, ppvClassObject=%p)\n", debugstr_guid(rclsid), debugstr_guid(riid), 
          ppvClassObj);

    /* Figure if there is an 'Instance' subkey for the given CLSID and acquire a handle. */
    if (!StringFromGUID2(rclsid, wszInstanceKey + 6, CHARS_IN_GUID))
        return CLASS_E_CLASSNOTAVAILABLE;
    wszInstanceKey[5+CHARS_IN_GUID] = '\\'; /* Repair the null-termination. */
    if (ERROR_SUCCESS != RegOpenKeyExW(HKEY_CLASSES_ROOT, wszInstanceKey, 0, KEY_READ, &hInstanceKey))
        /* If there is no 'Instance' subkey, then it's not a Shell Instance Object. */
        return CLASS_E_CLASSNOTAVAILABLE;

    if (ERROR_SUCCESS != RegQueryValueExW(hInstanceKey, wszCLSID, NULL, &dwType, (LPBYTE)wszCLSIDInstance, &cbBytes) ||
        FAILED(CLSIDFromString(wszCLSIDInstance, &clsidInstance)))
    {
        /* 'Instance' should have a 'CLSID' value with a well-formed clsid-string. */
        FIXME("Failed to infer instance CLSID! %s\n", debugstr_w(wszCLSIDInstance));
        RegCloseKey(hInstanceKey);
        return CLASS_E_CLASSNOTAVAILABLE;
    }

    /* Try to open the 'InitPropertyBag' subkey. */
    res = RegOpenKeyExW(hInstanceKey, wszInitPropertyBag, 0, KEY_READ, &hInitPropertyBagKey);
    RegCloseKey(hInstanceKey);
    if (res != ERROR_SUCCESS) {
        /* Besides 'InitPropertyBag's, shell instance objects might be initialized by streams.
         * So this case might not be an error. */
        TRACE("No InitPropertyBag key found!\n");
        return CLASS_E_CLASSNOTAVAILABLE;
    }

    /* If the construction succeeds, the new RegistryPropertyBag is responsible for closing
     * hInitPropertyBagKey. */
    hr = RegistryPropertyBag_Constructor(hInitPropertyBagKey, &IID_IPropertyBag,
                                         (LPVOID*)&pInitPropertyBag);
    if (FAILED(hr)) {
        RegCloseKey(hInitPropertyBagKey);
        return hr;
    }

    /* Construct an Instance Object Factory, which creates objects of class 'clsidInstance'
     * and asks them to initialize themselves with the help of the 'pInitiPropertyBag' */
    hr = InstanceObjectFactory_Constructor(&clsidInstance, pInitPropertyBag, riid, ppvClassObj);
    IPropertyBag_Release(pInitPropertyBag); /* The factory will hold a reference the bag. */
        
    return hr;
}