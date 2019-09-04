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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  const* REFCLSID ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  CATID ;

/* Variables and functions */
 int CHARS_IN_GUID ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ E_POINTER ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int KEY_READ ; 
 int KEY_WRITE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 scalar_t__ StringFromGUID2 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * clsid_keyname ; 
 scalar_t__ create_classes_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT COMCAT_RegisterClassCategories(
    REFCLSID rclsid,
    LPCWSTR type,
    ULONG cCategories,
    const CATID *rgcatid)
{
    WCHAR keyname[CHARS_IN_GUID];
    HRESULT res;
    HKEY clsid_key, class_key, type_key;

    if (cCategories && rgcatid == NULL) return E_POINTER;

    /* Format the class key name. */
    res = StringFromGUID2(rclsid, keyname, CHARS_IN_GUID);
    if (FAILED(res)) return res;

    /* Create (or open) the CLSID key. */
    res = create_classes_key(HKEY_CLASSES_ROOT, clsid_keyname, KEY_READ|KEY_WRITE, &clsid_key);
    if (res != ERROR_SUCCESS) return E_FAIL;

    /* Create (or open) the class key. */
    res = create_classes_key(clsid_key, keyname, KEY_READ|KEY_WRITE, &class_key);
    if (res == ERROR_SUCCESS) {
	/* Create (or open) the category type key. */
	res = create_classes_key(class_key, type, KEY_READ|KEY_WRITE, &type_key);
	if (res == ERROR_SUCCESS) {
	    for (; cCategories; --cCategories, ++rgcatid) {
		HKEY key;

		/* Format the category key name. */
		res = StringFromGUID2(rgcatid, keyname, CHARS_IN_GUID);
		if (FAILED(res)) continue;

		/* Do the register. */
		res = create_classes_key(type_key, keyname, KEY_READ|KEY_WRITE, &key);
		if (res == ERROR_SUCCESS) RegCloseKey(key);
	    }
	    res = S_OK;
	} else res = E_FAIL;
	RegCloseKey(class_key);
    } else res = E_FAIL;
    RegCloseKey(clsid_key);

    return res;
}