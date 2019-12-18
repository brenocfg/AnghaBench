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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  MIMECPINFO ;
typedef  int /*<<< orphan*/  IMultiLanguage ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IMultiLanguage_GetCodePageInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMultiLanguage_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_mlang (int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT mlang_getcodepageinfo(UINT cp, MIMECPINFO *mlang_cp_info)
{
    HRESULT hr;
    IMultiLanguage *ml;

    hr = get_mlang(&ml);

    if(SUCCEEDED(hr))
    {
        hr = IMultiLanguage_GetCodePageInfo(ml, cp, mlang_cp_info);
        IMultiLanguage_Release(ml);
    }
    return hr;
}