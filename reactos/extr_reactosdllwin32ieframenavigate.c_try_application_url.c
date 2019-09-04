#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  exec_info ;
typedef  unsigned char WCHAR ;
struct TYPE_4__ {int cbSize; int /*<<< orphan*/  nShow; int /*<<< orphan*/  lpFile; } ;
typedef  TYPE_1__ SHELLEXECUTEINFOW ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (unsigned char*) ; 
 int /*<<< orphan*/  CoInternetParseUrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  PARSE_SCHEMA ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  ShellExecuteExW (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (unsigned char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL try_application_url(LPCWSTR url)
{
    SHELLEXECUTEINFOW exec_info;
    WCHAR app[64];
    HKEY hkey;
    DWORD res, type;
    HRESULT hres;

    static const WCHAR wszURLProtocol[] = {'U','R','L',' ','P','r','o','t','o','c','o','l',0};

    hres = CoInternetParseUrl(url, PARSE_SCHEMA, 0, app, ARRAY_SIZE(app), NULL, 0);
    if(FAILED(hres))
        return FALSE;

    res = RegOpenKeyW(HKEY_CLASSES_ROOT, app, &hkey);
    if(res != ERROR_SUCCESS)
        return FALSE;

    res = RegQueryValueExW(hkey, wszURLProtocol, NULL, &type, NULL, NULL);
    RegCloseKey(hkey);
    if(res != ERROR_SUCCESS || type != REG_SZ)
        return FALSE;

    TRACE("opening application %s\n", debugstr_w(app));

    memset(&exec_info, 0, sizeof(exec_info));
    exec_info.cbSize = sizeof(exec_info);
    exec_info.lpFile = url;
    exec_info.nShow = SW_SHOW;

    return ShellExecuteExW(&exec_info);
}