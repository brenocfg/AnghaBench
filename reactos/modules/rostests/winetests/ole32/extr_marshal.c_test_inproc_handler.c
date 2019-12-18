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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_HANDLER ; 
 int /*<<< orphan*/  CLSID_WineTest ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  E_NOINTERFACE ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_IOleObject ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IID_IWineTest ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_ole_success (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reg_unreg_wine_test_class (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_inproc_handler(void)
{
    HRESULT hr;
    IUnknown *pObject;
    IUnknown *pObject2;

    if (FAILED(reg_unreg_wine_test_class(TRUE)))
        return;

    hr = CoCreateInstance(&CLSID_WineTest, NULL, CLSCTX_INPROC_HANDLER, &IID_IUnknown, (void **)&pObject);
    ok_ole_success(hr, "CoCreateInstance");

    if (SUCCEEDED(hr))
    {
        hr = IUnknown_QueryInterface(pObject, &IID_IWineTest, (void **)&pObject2);
        ok(hr == E_NOINTERFACE, "IUnknown_QueryInterface on handler for invalid interface returned 0x%08x instead of E_NOINTERFACE\n", hr);

        /* it's a handler as it supports IOleObject */
        hr = IUnknown_QueryInterface(pObject, &IID_IOleObject, (void **)&pObject2);
        ok_ole_success(hr, "IUnknown_QueryInterface(&IID_IOleObject)");
        IUnknown_Release(pObject2);

        IUnknown_Release(pObject);
    }

    reg_unreg_wine_test_class(FALSE);
}