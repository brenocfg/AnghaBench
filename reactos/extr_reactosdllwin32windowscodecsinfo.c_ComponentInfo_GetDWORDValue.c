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
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (scalar_t__) ; 
 int /*<<< orphan*/  RRF_RT_DWORD ; 
 scalar_t__ RegGetValueW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT ComponentInfo_GetDWORDValue(HKEY classkey, LPCWSTR value,
    DWORD *result)
{
    LONG ret;
    DWORD cbdata = sizeof(DWORD);

    if (!result)
        return E_INVALIDARG;

    ret = RegGetValueW(classkey, NULL, value, RRF_RT_DWORD, NULL,
        result, &cbdata);

    if (ret == ERROR_FILE_NOT_FOUND)
    {
        *result = 0;
        return S_OK;
    }

    return HRESULT_FROM_WIN32(ret);
}