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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  IUriBuilder ;
typedef  int /*<<< orphan*/  IUri ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_POINTER ; 
 int /*<<< orphan*/  IUriBuilder_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 scalar_t__ get_refcnt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  http_urlW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pCreateIUriBuilder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ pCreateUri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void test_CreateIUriBuilder(void) {
    HRESULT hr;
    IUriBuilder *builder = NULL;
    IUri *uri;

    hr = pCreateIUriBuilder(NULL, 0, 0, NULL);
    ok(hr == E_POINTER, "Error: CreateIUriBuilder returned 0x%08x, expected 0x%08x\n",
        hr, E_POINTER);

    /* CreateIUriBuilder increases the ref count of the IUri it receives. */
    hr = pCreateUri(http_urlW, 0, 0, &uri);
    ok(hr == S_OK, "Error: CreateUri returned 0x%08x, expected 0x%08x.\n", hr, S_OK);
    if(SUCCEEDED(hr)) {
        ULONG cur_count, orig_count;

        orig_count = get_refcnt(uri);
        hr = pCreateIUriBuilder(uri, 0, 0, &builder);
        ok(hr == S_OK, "Error: CreateIUriBuilder returned 0x%08x, expected 0x%08x.\n", hr, S_OK);
        ok(builder != NULL, "Error: Expecting builder not to be NULL\n");

        cur_count = get_refcnt(uri);
        ok(cur_count == orig_count+1, "Error: Expected the ref count to be %u, but was %u instead.\n", orig_count+1, cur_count);

        if(builder) IUriBuilder_Release(builder);
        cur_count = get_refcnt(uri);
        ok(cur_count == orig_count, "Error: Expected the ref count to be %u, but was %u instead.\n", orig_count, cur_count);
    }
    if(uri) IUri_Release(uri);
}