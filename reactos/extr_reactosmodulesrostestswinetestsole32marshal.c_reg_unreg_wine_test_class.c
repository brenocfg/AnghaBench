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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  LPOLESTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_WineTest ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  KEY_SET_VALUE ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RegSetValueExA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  StringFromCLSID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_ole_success (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static HRESULT reg_unreg_wine_test_class(BOOL Register)
{
    HRESULT hr;
    char buffer[256];
    LPOLESTR pszClsid;
    HKEY hkey;
    DWORD dwDisposition;
    DWORD error;

    hr = StringFromCLSID(&CLSID_WineTest, &pszClsid);
    ok_ole_success(hr, "StringFromCLSID");
    strcpy(buffer, "CLSID\\");
    WideCharToMultiByte(CP_ACP, 0, pszClsid, -1, buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), NULL, NULL);
    CoTaskMemFree(pszClsid);
    strcat(buffer, "\\InprocHandler32");
    if (Register)
    {
        error = RegCreateKeyExA(HKEY_CLASSES_ROOT, buffer, 0, NULL, 0, KEY_SET_VALUE, NULL, &hkey, &dwDisposition);
        if (error == ERROR_ACCESS_DENIED)
        {
            skip("Not authorized to modify the Classes key\n");
            return E_FAIL;
        }
        ok(error == ERROR_SUCCESS, "RegCreateKeyEx failed with error %d\n", error);
        if (error != ERROR_SUCCESS) hr = E_FAIL;
        error = RegSetValueExA(hkey, NULL, 0, REG_SZ, (const unsigned char *)"\"ole32.dll\"", strlen("\"ole32.dll\"") + 1);
        ok(error == ERROR_SUCCESS, "RegSetValueEx failed with error %d\n", error);
        if (error != ERROR_SUCCESS) hr = E_FAIL;
        RegCloseKey(hkey);
    }
    else
    {
        RegDeleteKeyA(HKEY_CLASSES_ROOT, buffer);
        *strrchr(buffer, '\\') = '\0';
        RegDeleteKeyA(HKEY_CLASSES_ROOT, buffer);
    }
    return hr;
}