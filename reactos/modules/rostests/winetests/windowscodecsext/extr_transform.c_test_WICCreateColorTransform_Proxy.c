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
typedef  int /*<<< orphan*/  IWICColorTransform ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  COINIT_APARTMENTTHREADED ; 
 int /*<<< orphan*/  COINIT_MULTITHREADED ; 
 scalar_t__ CoInitializeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  IWICColorTransform_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 scalar_t__ WICCreateColorTransform_Proxy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_WICCreateColorTransform_Proxy(void)
{
    HRESULT hr;
    IWICColorTransform *transform;

    hr = WICCreateColorTransform_Proxy( NULL );
    ok( hr == E_INVALIDARG, "got %08x\n", hr );

    transform = NULL;
    hr = WICCreateColorTransform_Proxy( &transform );
    ok( hr == S_OK, "got %08x\n", hr );
    if (transform) IWICColorTransform_Release( transform );

    hr = CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );
    ok( hr == S_OK, "got %08x\n", hr );

    transform = NULL;
    hr = WICCreateColorTransform_Proxy( &transform );
    ok( hr == S_OK, "got %08x\n", hr );
    if (transform) IWICColorTransform_Release( transform );
    CoUninitialize();

    hr = CoInitializeEx( NULL, COINIT_MULTITHREADED );
    ok( hr == S_OK, "got %08x\n", hr );

    transform = NULL;
    hr = WICCreateColorTransform_Proxy( &transform );
    ok( hr == S_OK, "got %08x\n", hr );
    if (transform) IWICColorTransform_Release( transform );
    CoUninitialize();
}