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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  IAssemblyCacheItem ;
typedef  int /*<<< orphan*/  IAssemblyCache ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  IAssemblyCacheItem_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IAssemblyCache_CreateAssemblyCacheItem (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  IAssemblyCache_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pCreateAssemblyCache (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_CreateAssemblyCacheItem(void)
{
    IAssemblyCache *cache;
    IAssemblyCacheItem *item;
    HRESULT hr;

    static const WCHAR wine[] = {'w','i','n','e',0};

    hr = pCreateAssemblyCache(&cache, 0);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    hr = IAssemblyCache_CreateAssemblyCacheItem(cache, 0, NULL, NULL, NULL);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %08x\n", hr);

    hr = IAssemblyCache_CreateAssemblyCacheItem(cache, 0, NULL, &item, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    IAssemblyCacheItem_Release(item);

    hr = IAssemblyCache_CreateAssemblyCacheItem(cache, 0, NULL, &item, wine);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    IAssemblyCacheItem_Release(item);

    hr = IAssemblyCache_CreateAssemblyCacheItem(cache, 1, (void *)0xdeadbeef, &item, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    IAssemblyCacheItem_Release(item);

    hr = IAssemblyCache_CreateAssemblyCacheItem(cache, 1, NULL, &item, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    IAssemblyCacheItem_Release(item);

    hr = IAssemblyCache_CreateAssemblyCacheItem(cache, 0, (void *)0xdeadbeef, &item, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    IAssemblyCacheItem_Release(item);

    IAssemblyCache_Release(cache);
}