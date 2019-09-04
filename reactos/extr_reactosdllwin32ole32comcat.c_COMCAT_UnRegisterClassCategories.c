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
typedef  char WCHAR ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  const* REFCLSID ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  CATID ;

/* Variables and functions */
 int /*<<< orphan*/  CHARS_IN_GUID ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ E_POINTER ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int KEY_READ ; 
 int KEY_WRITE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegDeleteKeyW (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ S_OK ; 
 scalar_t__ StringFromGUID2 (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyW (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ open_classes_key (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT COMCAT_UnRegisterClassCategories(
    REFCLSID rclsid,
    LPCWSTR type,
    ULONG cCategories,
    const CATID *rgcatid)
{
    WCHAR keyname[68] = { 'C', 'L', 'S', 'I', 'D', '\\' };
    HRESULT res;
    HKEY type_key;

    if (cCategories && rgcatid == NULL) return E_POINTER;

    /* Format the class category type key name. */
    res = StringFromGUID2(rclsid, keyname + 6, CHARS_IN_GUID);
    if (FAILED(res)) return res;
    keyname[44] = '\\';
    lstrcpyW(keyname + 45, type);

    /* Open the class category type key. */
    res = open_classes_key(HKEY_CLASSES_ROOT, keyname, KEY_READ|KEY_WRITE, &type_key);
    if (res != ERROR_SUCCESS) return E_FAIL;

    for (; cCategories; --cCategories, ++rgcatid) {
	/* Format the category key name. */
	res = StringFromGUID2(rgcatid, keyname, CHARS_IN_GUID);
	if (FAILED(res)) continue;

	/* Do the unregister. */
	RegDeleteKeyW(type_key, keyname);
    }
    RegCloseKey(type_key);

    return S_OK;
}