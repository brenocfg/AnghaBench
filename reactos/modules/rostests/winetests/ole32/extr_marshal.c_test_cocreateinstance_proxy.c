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
typedef  int /*<<< orphan*/  IMultiQI ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC ; 
 int /*<<< orphan*/  CLSID_ShellDesktop ; 
 int /*<<< orphan*/  COINIT_MULTITHREADED ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  IID_IMultiQI ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IMultiQI_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  ok_ole_success (scalar_t__,scalar_t__ (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**)) ; 
 int /*<<< orphan*/  pCoInitializeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_cocreateinstance_proxy(void)
{
    IUnknown *pProxy;
    IMultiQI *pMQI;
    HRESULT hr;

    pCoInitializeEx(NULL, COINIT_MULTITHREADED);

    hr = CoCreateInstance(&CLSID_ShellDesktop, NULL, CLSCTX_INPROC, &IID_IUnknown, (void **)&pProxy);
    ok_ole_success(hr, CoCreateInstance);
    hr = IUnknown_QueryInterface(pProxy, &IID_IMultiQI, (void **)&pMQI);
    ok(hr == S_OK, "created object is not a proxy, so was created in the wrong apartment\n");
    if (hr == S_OK)
        IMultiQI_Release(pMQI);
    IUnknown_Release(pProxy);

    CoUninitialize();
}