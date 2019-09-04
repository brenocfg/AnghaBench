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
typedef  int UINT ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_MORE_DATA ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (scalar_t__) ; 
 int RRF_NOEXPAND ; 
 int RRF_RT_REG_SZ ; 
 scalar_t__ RegGetValueW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WINCODEC_ERR_INSUFFICIENTBUFFER ; 

__attribute__((used)) static HRESULT ComponentInfo_GetStringValue(HKEY classkey, LPCWSTR value,
    UINT buffer_size, WCHAR *buffer, UINT *actual_size)
{
    LONG ret;
    DWORD cbdata=buffer_size * sizeof(WCHAR);

    if (!actual_size)
        return E_INVALIDARG;

    ret = RegGetValueW(classkey, NULL, value, RRF_RT_REG_SZ|RRF_NOEXPAND, NULL,
        buffer, &cbdata);

    if (ret == ERROR_FILE_NOT_FOUND)
    {
        *actual_size = 0;
        return S_OK;
    }

    if (ret == 0 || ret == ERROR_MORE_DATA)
        *actual_size = cbdata/sizeof(WCHAR);

    if (!buffer && buffer_size != 0)
        /* Yes, native returns the correct size in this case. */
        return E_INVALIDARG;

    if (ret == ERROR_MORE_DATA)
        return WINCODEC_ERR_INSUFFICIENTBUFFER;

    return HRESULT_FROM_WIN32(ret);
}