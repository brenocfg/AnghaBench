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
typedef  int /*<<< orphan*/  wszPageName ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  DocHost ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int MAX_PATH ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  navigate_url (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT go_home(DocHost *This)
{
    HKEY hkey;
    DWORD res, type, size;
    WCHAR wszPageName[MAX_PATH];
    static const WCHAR wszAboutBlank[] = {'a','b','o','u','t',':','b','l','a','n','k',0};
    static const WCHAR wszStartPage[] = {'S','t','a','r','t',' ','P','a','g','e',0};
    static const WCHAR wszSubKey[] = {'S','o','f','t','w','a','r','e','\\',
                                      'M','i','c','r','o','s','o','f','t','\\',
                                      'I','n','t','e','r','n','e','t',' ','E','x','p','l','o','r','e','r','\\',
                                      'M','a','i','n',0};

    res = RegOpenKeyW(HKEY_CURRENT_USER, wszSubKey, &hkey);
    if (res != ERROR_SUCCESS)
        return navigate_url(This, wszAboutBlank, NULL, NULL, NULL, NULL);

    size = sizeof(wszPageName);
    res = RegQueryValueExW(hkey, wszStartPage, NULL, &type, (LPBYTE)wszPageName, &size);
    RegCloseKey(hkey);
    if (res != ERROR_SUCCESS || type != REG_SZ)
        return navigate_url(This, wszAboutBlank, NULL, NULL, NULL, NULL);

    return navigate_url(This, wszPageName, NULL, NULL, NULL, NULL);
}