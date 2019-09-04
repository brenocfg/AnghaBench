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
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CreateBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMoniker_Reduce (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  MKRREDUCE_ALL ; 

__attribute__((used)) static HRESULT reduce_moniker(IMoniker *pmk, IBindCtx *pbc, IMoniker **pmkReduced)
{
    IBindCtx *pbcNew = NULL;
    HRESULT hr;
    if (!pbc)
    {
        hr = CreateBindCtx(0, &pbcNew);
        if (FAILED(hr))
            return hr;
        pbc = pbcNew;
    }
    hr = IMoniker_Reduce(pmk, pbc, MKRREDUCE_ALL, NULL, pmkReduced);
    if (FAILED(hr))
        ERR("reducing moniker failed with error 0x%08x\n", hr);
    if (pbcNew) IBindCtx_Release(pbcNew);
    return hr;
}