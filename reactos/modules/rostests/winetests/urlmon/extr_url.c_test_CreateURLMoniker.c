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
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/ * HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateURLMoniker (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * E_INVALIDARG ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MK_E_SYNTAX ; 
 int /*<<< orphan*/ * S_OK ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/ * emptyW ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_CreateURLMoniker(LPCWSTR url1, LPCWSTR url2)
{
    HRESULT hr;
    IMoniker *mon1 = NULL;
    IMoniker *mon2 = NULL;

    hr = CreateURLMoniker(NULL, NULL, NULL);
    ok(hr == E_INVALIDARG,
       "Expected CreateURLMoniker to return E_INVALIDARG, got 0x%08x\n", hr);

    mon1 = (IMoniker *)0xdeadbeef;
    hr = CreateURLMoniker(NULL, NULL, &mon1);
    ok(hr == E_INVALIDARG,
       "Expected CreateURLMoniker to return E_INVALIDARG, got 0x%08x\n", hr);
    ok(mon1 == NULL, "Expected the output pointer to be NULL, got %p\n", mon1);

    hr = CreateURLMoniker(NULL, emptyW, NULL);
    ok(hr == E_INVALIDARG,
       "Expected CreateURLMoniker to return E_INVALIDARG, got 0x%08x\n", hr);

    hr = CreateURLMoniker(NULL, emptyW, &mon1);
    ok(hr == S_OK ||
       broken(hr == MK_E_SYNTAX), /* IE5/IE5.01/IE6 SP2 */
       "Expected CreateURLMoniker to return S_OK, got 0x%08x\n", hr);
    if(mon1) IMoniker_Release(mon1);

    hr = CreateURLMoniker(NULL, url1, &mon1);
    ok(hr == S_OK, "failed to create moniker: 0x%08x\n", hr);
    if(hr == S_OK) {
        hr = CreateURLMoniker(mon1, url2, &mon2);
        ok(hr == S_OK, "failed to create moniker: 0x%08x\n", hr);
    }
    if(mon1) IMoniker_Release(mon1);
    if(mon2) IMoniker_Release(mon2);
}