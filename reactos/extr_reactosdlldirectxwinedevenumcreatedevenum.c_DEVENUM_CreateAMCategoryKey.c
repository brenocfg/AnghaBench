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
typedef  int /*<<< orphan*/  wszRegKey ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegCreateKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wszActiveMovieKey ; 

__attribute__((used)) static HRESULT DEVENUM_CreateAMCategoryKey(const CLSID * clsidCategory)
{
    WCHAR wszRegKey[MAX_PATH];
    HRESULT res = S_OK;
    HKEY hkeyDummy = NULL;

    strcpyW(wszRegKey, wszActiveMovieKey);

    if (!StringFromGUID2(clsidCategory, wszRegKey + strlenW(wszRegKey), sizeof(wszRegKey)/sizeof(wszRegKey[0]) - strlenW(wszRegKey)))
        res = E_INVALIDARG;

    if (SUCCEEDED(res))
    {
        LONG lRes = RegCreateKeyW(HKEY_CURRENT_USER, wszRegKey, &hkeyDummy);
        res = HRESULT_FROM_WIN32(lRes);
    }

    if (hkeyDummy)
        RegCloseKey(hkeyDummy);

    if (FAILED(res))
        ERR("Failed to create key HKEY_CURRENT_USER\\%s\n", debugstr_w(wszRegKey));

    return res;
}