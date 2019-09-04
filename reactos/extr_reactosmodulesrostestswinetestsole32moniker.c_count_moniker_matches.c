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
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IEnumMoniker ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 scalar_t__ IEnumMoniker_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMoniker_GetDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  lstrcmpiW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*,int) ; 
 int /*<<< orphan*/  wszFileName1 ; 
 int /*<<< orphan*/  wszFileName2 ; 

__attribute__((used)) static int count_moniker_matches(IBindCtx * pbc, IEnumMoniker * spEM)
{
    IMoniker * spMoniker;
    int monCnt=0, matchCnt=0;

    while ((IEnumMoniker_Next(spEM, 1, &spMoniker, NULL)==S_OK))
    {
        HRESULT hr;
        WCHAR * szDisplayn;
        monCnt++;
        hr=IMoniker_GetDisplayName(spMoniker, pbc, NULL, &szDisplayn);
        if (SUCCEEDED(hr))
        {
            if (!lstrcmpiW(szDisplayn, wszFileName1) || !lstrcmpiW(szDisplayn, wszFileName2))
                matchCnt++;
            CoTaskMemFree(szDisplayn);
        }
    }
    trace("Total number of monikers is %i\n", monCnt);
    return matchCnt;
}