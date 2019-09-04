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
typedef  int /*<<< orphan*/  wszProtocolsKey ;
typedef  int /*<<< orphan*/  str_clsid ;
typedef  char WCHAR ;
typedef  scalar_t__ LPWSTR ;
typedef  char const* LPCWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  IClassFactory ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (char const*) ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int CLSIDFromString (char*,int /*<<< orphan*/ *) ; 
 int CoGetClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int ERROR_SUCCESS ; 
 scalar_t__ FAILED (int) ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  IID_IClassFactory ; 
 int MK_E_SYNTAX ; 
 int REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 int RegOpenKeyW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ **) ; 
 int RegQueryValueExW (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ SUCCEEDED (int) ; 
 int S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 scalar_t__ heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 

__attribute__((used)) static HRESULT get_protocol_cf(LPCWSTR schema, DWORD schema_len, CLSID *pclsid, IClassFactory **ret)
{
    WCHAR str_clsid[64];
    HKEY hkey = NULL;
    DWORD res, type, size;
    CLSID clsid;
    LPWSTR wszKey;
    HRESULT hres;

    static const WCHAR wszProtocolsKey[] =
        {'P','R','O','T','O','C','O','L','S','\\','H','a','n','d','l','e','r','\\'};
    static const WCHAR wszCLSID[] = {'C','L','S','I','D',0};

    wszKey = heap_alloc(sizeof(wszProtocolsKey)+(schema_len+1)*sizeof(WCHAR));
    memcpy(wszKey, wszProtocolsKey, sizeof(wszProtocolsKey));
    memcpy(wszKey + ARRAY_SIZE(wszProtocolsKey), schema, (schema_len+1)*sizeof(WCHAR));

    res = RegOpenKeyW(HKEY_CLASSES_ROOT, wszKey, &hkey);
    heap_free(wszKey);
    if(res != ERROR_SUCCESS) {
        TRACE("Could not open protocol handler key\n");
        return MK_E_SYNTAX;
    }
    
    size = sizeof(str_clsid);
    res = RegQueryValueExW(hkey, wszCLSID, NULL, &type, (LPBYTE)str_clsid, &size);
    RegCloseKey(hkey);
    if(res != ERROR_SUCCESS || type != REG_SZ) {
        WARN("Could not get protocol CLSID res=%d\n", res);
        return MK_E_SYNTAX;
    }

    hres = CLSIDFromString(str_clsid, &clsid);
    if(FAILED(hres)) {
        WARN("CLSIDFromString failed: %08x\n", hres);
        return hres;
    }

    if(pclsid)
        *pclsid = clsid;

    if(!ret)
        return S_OK;

    hres = CoGetClassObject(&clsid, CLSCTX_INPROC_SERVER, NULL, &IID_IClassFactory, (void**)ret);
    return SUCCEEDED(hres) ? S_OK : MK_E_SYNTAX;
}