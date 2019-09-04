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
typedef  int /*<<< orphan*/  mime ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 char* CoTaskMemAlloc (scalar_t__) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (scalar_t__) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 

HRESULT find_mime_from_ext(const WCHAR *ext, WCHAR **ret)
{
    DWORD res, size;
    WCHAR mime[64];
    HKEY hkey;

    static const WCHAR content_typeW[] = {'C','o','n','t','e','n','t',' ','T','y','p','e','\0'};

    res = RegOpenKeyW(HKEY_CLASSES_ROOT, ext, &hkey);
    if(res != ERROR_SUCCESS)
        return HRESULT_FROM_WIN32(res);

    size = sizeof(mime);
    res = RegQueryValueExW(hkey, content_typeW, NULL, NULL, (LPBYTE)mime, &size);
    RegCloseKey(hkey);
    if(res != ERROR_SUCCESS)
        return HRESULT_FROM_WIN32(res);

    TRACE("found MIME %s\n", debugstr_w(mime));

    *ret = CoTaskMemAlloc(size);
    memcpy(*ret, mime, size);
    return S_OK;
}