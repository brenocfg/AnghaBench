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
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALIDARG ; 
 char const* http_urlW ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  pCreateUri (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void test_CreateUri_InvalidArgs(void) {
    HRESULT hr;
    IUri *uri = (void*) 0xdeadbeef;

    const WCHAR invalidW[] = {'i','n','v','a','l','i','d',0};
    static const WCHAR emptyW[] = {0};

    hr = pCreateUri(http_urlW, 0, 0, NULL);
    ok(hr == E_INVALIDARG, "Error: CreateUri returned 0x%08x, expected 0x%08x\n", hr, E_INVALIDARG);

    hr = pCreateUri(NULL, 0, 0, &uri);
    ok(hr == E_INVALIDARG, "Error: CreateUri returned 0x%08x, expected 0x%08x\n", hr, E_INVALIDARG);
    ok(uri == NULL, "Error: Expected the IUri to be NULL, but it was %p instead\n", uri);

    uri = (void*) 0xdeadbeef;
    hr = pCreateUri(invalidW, 0, 0, &uri);
    ok(hr == E_INVALIDARG, "Error: CreateUri returned 0x%08x, expected 0x%08x.\n", hr, E_INVALIDARG);
    ok(uri == NULL, "Error: Expected the IUri to be NULL, but it was %p instead\n", uri);

    uri = (void*) 0xdeadbeef;
    hr = pCreateUri(emptyW, 0, 0, &uri);
    ok(hr == E_INVALIDARG, "Error: CreateUri returned 0x%08x, expected 0x%08x.\n", hr, E_INVALIDARG);
    ok(uri == NULL, "Error: Expected the IUri to be NULL, but it was %p instead\n", uri);
}