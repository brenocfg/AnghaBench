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
typedef  int ULONG ;
typedef  scalar_t__* PWCHAR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  LCID ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ CAT_E_NODESCRIPTION ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ REG_SZ ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  wsprintfW (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT COMCAT_GetCategoryDesc(HKEY key, LCID lcid, PWCHAR pszDesc,
				      ULONG buf_wchars)
{
    static const WCHAR fmt[] = { '%', 'l', 'X', 0 };
    WCHAR valname[5];
    HRESULT res;
    DWORD type, size = (buf_wchars - 1) * sizeof(WCHAR);

    if (pszDesc == NULL) return E_INVALIDARG;

    /* FIXME: lcid comparisons are more complex than this! */
    wsprintfW(valname, fmt, lcid);
    res = RegQueryValueExW(key, valname, 0, &type, (LPBYTE)pszDesc, &size);
    if (res != ERROR_SUCCESS || type != REG_SZ) {
	FIXME("Simplified lcid comparison\n");
	return CAT_E_NODESCRIPTION;
    }
    pszDesc[size / sizeof(WCHAR)] = 0;

    return S_OK;
}