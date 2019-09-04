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
 int /*<<< orphan*/ * http_urlW ; 
 int /*<<< orphan*/ * http_url_fragW ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  pCreateUriWithFragment (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void test_CreateUriWithFragment_InvalidArgs(void) {
    HRESULT hr;
    IUri *uri = (void*) 0xdeadbeef;
    const WCHAR fragmentW[] = {'#','f','r','a','g','m','e','n','t',0};

    hr = pCreateUriWithFragment(NULL, fragmentW, 0, 0, &uri);
    ok(hr == E_INVALIDARG, "Error: CreateUriWithFragment returned 0x%08x, expected 0x%08x.\n", hr, E_INVALIDARG);
    ok(uri == NULL, "Error: Expected uri to be NULL, but was %p instead.\n", uri);

    hr = pCreateUriWithFragment(http_urlW, fragmentW, 0, 0, NULL);
    ok(hr == E_INVALIDARG, "Error: CreateUriWithFragment returned 0x%08x, expected 0x%08x.\n", hr, E_INVALIDARG);

    /* Original URI can't already contain a fragment component. */
    uri = (void*) 0xdeadbeef;
    hr = pCreateUriWithFragment(http_url_fragW, fragmentW, 0, 0, &uri);
    ok(hr == E_INVALIDARG, "Error: CreateUriWithFragment returned 0x%08x, expected 0x%08x.\n", hr, E_INVALIDARG);
    ok(uri == NULL, "Error: Expected uri to be NULL, but was %p instead.\n", uri);
}