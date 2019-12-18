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
typedef  int /*<<< orphan*/  MIMECSETINFO ;
typedef  int /*<<< orphan*/  IMultiLanguage ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMultiLanguage_GetCharsetInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMultiLanguage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MIME_E_NOT_FOUND ; 
 scalar_t__ MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SysAllocStringLen (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_mlang (int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT mlang_getcsetinfo(const char *charset, MIMECSETINFO *mlang_info)
{
    DWORD len = MultiByteToWideChar(CP_ACP, 0, charset, -1, NULL, 0);
    BSTR bstr = SysAllocStringLen(NULL, len - 1);
    HRESULT hr;
    IMultiLanguage *ml;

    MultiByteToWideChar(CP_ACP, 0, charset, -1, bstr, len);

    hr = get_mlang(&ml);

    if(SUCCEEDED(hr))
    {
        hr = IMultiLanguage_GetCharsetInfo(ml, bstr, mlang_info);
        IMultiLanguage_Release(ml);
    }
    SysFreeString(bstr);
    if(FAILED(hr)) hr = MIME_E_NOT_FOUND;
    return hr;
}