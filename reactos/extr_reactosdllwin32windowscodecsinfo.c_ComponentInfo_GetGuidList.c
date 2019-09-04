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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CLSIDFromString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_NO_MORE_ITEMS ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (scalar_t__) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryInfoKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT ComponentInfo_GetGuidList(HKEY classkey, LPCWSTR subkeyname,
    UINT buffersize, GUID *buffer, UINT *actual_size)
{
    LONG ret;
    HKEY subkey;
    UINT items_returned;
    WCHAR guid_string[39];
    DWORD guid_string_size;
    HRESULT hr=S_OK;

    if (!actual_size)
        return E_INVALIDARG;

    ret = RegOpenKeyExW(classkey, subkeyname, 0, KEY_READ, &subkey);
    if (ret == ERROR_FILE_NOT_FOUND)
    {
        *actual_size = 0;
        return S_OK;
    }
    else if (ret != ERROR_SUCCESS) return HRESULT_FROM_WIN32(ret);

    if (buffer)
    {
        items_returned = 0;
        guid_string_size = 39;
        while (items_returned < buffersize)
        {
            ret = RegEnumKeyExW(subkey, items_returned, guid_string,
                &guid_string_size, NULL, NULL, NULL, NULL);

            if (ret != ERROR_SUCCESS)
            {
                hr = HRESULT_FROM_WIN32(ret);
                break;
            }

            if (guid_string_size != 38)
            {
                hr = E_FAIL;
                break;
            }

            hr = CLSIDFromString(guid_string, &buffer[items_returned]);
            if (FAILED(hr))
                break;

            items_returned++;
            guid_string_size = 39;
        }

        if (ret == ERROR_NO_MORE_ITEMS)
            hr = S_OK;

        *actual_size = items_returned;
    }
    else
    {
        ret = RegQueryInfoKeyW(subkey, NULL, NULL, NULL, actual_size, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        if (ret != ERROR_SUCCESS)
            hr = HRESULT_FROM_WIN32(ret);
    }

    RegCloseKey(subkey);

    return hr;
}