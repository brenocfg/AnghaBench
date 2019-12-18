#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ IUnknown ;
typedef  int /*<<< orphan*/  IStillImageW ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  CLSCTX_ALL ; 
 int /*<<< orphan*/  CLSID_Sti ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IStillImageW ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IStillImage_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IStillImage_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IStillImage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  STI_VERSION_REAL ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 int /*<<< orphan*/  aggregator_addref_called ; 
 int /*<<< orphan*/  aggregator_vtbl ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pStiCreateInstanceW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,TYPE_1__*) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_stillimage_aggregation(void)
{
    if (pStiCreateInstanceW)
    {
        IUnknown aggregator = { &aggregator_vtbl };
        IStillImageW *pStiW;
        IUnknown *pUnknown;
        HRESULT hr;

        /* When aggregating, the outer object must get the non-delegating IUnknown to be
           able to control the inner object's reference count and query its interfaces.
           But StiCreateInstance* only take PSTI. So how does the non-delegating IUnknown
           come back to the outer object calling this function? */

        hr = pStiCreateInstanceW(GetModuleHandleA(NULL), STI_VERSION_REAL, &pStiW, &aggregator);
        if (SUCCEEDED(hr))
        {
            IStillImageW *pStiW2 = NULL;

            /* Does this interface delegate? */
            aggregator_addref_called = FALSE;
            IStillImage_AddRef(pStiW);
            ok(!aggregator_addref_called, "the aggregated IStillImageW shouldn't delegate\n");
            IStillImage_Release(pStiW);

            /* Tests show calling IStillImageW_WriteToErrorLog on the interface segfaults on Windows, so I guess it's an IUnknown.
               But querying for an IUnknown returns a different interface, which also delegates.
               So much for COM being reflexive...
               Anyway I doubt apps depend on any of this. */

            /* And what about the IStillImageW interface? */
            hr = IStillImage_QueryInterface(pStiW, &IID_IStillImageW, (void**)&pStiW2);
            if (SUCCEEDED(hr))
            {
                ok(pStiW != pStiW2, "the aggregated IStillImageW and its queried IStillImageW unexpectedly match\n");
                /* Does it delegate? */
                aggregator_addref_called = FALSE;
                IStillImage_AddRef(pStiW2);
                ok(aggregator_addref_called, "the created IStillImageW's IStillImageW should delegate\n");
                IStillImage_Release(pStiW2);
                IStillImage_Release(pStiW2);
            }
            else
                ok(0, "could not query for IID_IStillImageW, hr = 0x%x\n", hr);

            IStillImage_Release(pStiW);
        }
        else
            ok(0, "could not create StillImageW, hr = 0x%X\n", hr);

        /* Now do the above tests prove that STI.DLL isn't picky about querying for IUnknown
           in CoCreateInterface when aggregating? */
        hr = CoCreateInstance(&CLSID_Sti, &aggregator, CLSCTX_ALL, &IID_IStillImageW, (void**)&pStiW);
        ok(FAILED(hr), "CoCreateInstance unexpectedly succeeded when querying for IStillImageW during aggregation\n");
        if (SUCCEEDED(hr))
            IStillImage_Release(pStiW);
        hr = CoCreateInstance(&CLSID_Sti, &aggregator, CLSCTX_ALL, &IID_IUnknown, (void**)&pUnknown);
        ok(SUCCEEDED(hr) ||
            broken(hr == CLASS_E_NOAGGREGATION), /* Win 2000 */
                "CoCreateInstance unexpectedly failed when querying for IUnknown during aggregation, hr = 0x%x\n", hr);
        if (SUCCEEDED(hr))
            IUnknown_Release(pUnknown);
    }
    else
        skip("No StiCreateInstanceW function\n");
}