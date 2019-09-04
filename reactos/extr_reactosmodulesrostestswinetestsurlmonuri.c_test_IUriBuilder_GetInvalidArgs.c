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
typedef  int LPCWSTR ;
typedef  int /*<<< orphan*/  IUriBuilder ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_POINTER ; 
 int /*<<< orphan*/  IUriBuilder_GetFragment (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IUriBuilder_GetHost (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IUriBuilder_GetPassword (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IUriBuilder_GetPath (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IUriBuilder_GetPort (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IUriBuilder_GetQuery (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IUriBuilder_GetSchemeName (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IUriBuilder_GetUserName (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IUriBuilder_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  pCreateIUriBuilder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void test_IUriBuilder_GetInvalidArgs(void) {
    IUriBuilder *builder = NULL;
    HRESULT hr;

    hr = pCreateIUriBuilder(NULL, 0, 0, &builder);
    ok(hr == S_OK, "Error: CreateIUriBuilder returned 0x%08x, expected 0x%08x.\n", hr, S_OK);
    if(SUCCEEDED(hr)) {
        LPCWSTR received = (void*) 0xdeadbeef;
        DWORD len = -1, port = -1;
        BOOL set = -1;

        hr = IUriBuilder_GetFragment(builder, NULL, NULL);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetFragment returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        hr = IUriBuilder_GetFragment(builder, NULL, &received);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetFragment returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        ok(!received, "Error: Expected received to be NULL, but was %p instead.\n", received);
        hr = IUriBuilder_GetFragment(builder, &len, NULL);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetFragment returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        ok(!len, "Error: Expected len to be 0, but was %d instead.\n", len);

        hr = IUriBuilder_GetHost(builder, NULL, NULL);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetHost returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        received = (void*) 0xdeadbeef;
        hr = IUriBuilder_GetHost(builder, NULL, &received);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetHost returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        ok(!received, "Error: Expected received to be NULL, but was %p instead.\n", received);
        len = -1;
        hr = IUriBuilder_GetHost(builder, &len, NULL);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetHost returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        ok(!len, "Error: Expected len to be 0, but was %d instead.\n", len);

        hr = IUriBuilder_GetPassword(builder, NULL, NULL);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetPassword returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        received = (void*) 0xdeadbeef;
        hr = IUriBuilder_GetPassword(builder, NULL, &received);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetPassword returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        ok(!received, "Error: Expected received to be NULL, but was %p instead.\n", received);
        len = -1;
        hr = IUriBuilder_GetPassword(builder, &len, NULL);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetPassword returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        ok(!len, "Error: Expected len to be 0, but was %d instead.\n", len);

        hr = IUriBuilder_GetPath(builder, NULL, NULL);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetPath returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        received = (void*) 0xdeadbeef;
        hr = IUriBuilder_GetPath(builder, NULL, &received);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetPath returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        ok(!received, "Error: Expected received to be NULL, but was %p instead.\n", received);
        len = -1;
        hr = IUriBuilder_GetPath(builder, &len, NULL);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetPath returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        ok(!len, "Error: Expected len to be 0, but was %d instead.\n", len);

        hr = IUriBuilder_GetPort(builder, NULL, NULL);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetPort returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        hr = IUriBuilder_GetPort(builder, NULL, &port);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetPort returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        ok(!port, "Error: Expected port to be 0, but was %d instead.\n", port);
        hr = IUriBuilder_GetPort(builder, &set, NULL);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetPort returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        ok(!set, "Error: Expected set to be FALSE, but was %d instead.\n", set);

        hr = IUriBuilder_GetQuery(builder, NULL, NULL);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetQuery returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        received = (void*) 0xdeadbeef;
        hr = IUriBuilder_GetQuery(builder, NULL, &received);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetQuery returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        ok(!received, "Error: Expected received to be NULL, but was %p instead.\n", received);
        len = -1;
        hr = IUriBuilder_GetQuery(builder, &len, NULL);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetQuery returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        ok(!len, "Error: Expected len to be 0, but was %d instead.\n", len);

        hr = IUriBuilder_GetSchemeName(builder, NULL, NULL);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetSchemeName returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        received = (void*) 0xdeadbeef;
        hr = IUriBuilder_GetSchemeName(builder, NULL, &received);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetSchemeName returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        ok(!received, "Error: Expected received to be NULL, but was %p instead.\n", received);
        len = -1;
        hr = IUriBuilder_GetSchemeName(builder, &len, NULL);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetSchemeName returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        ok(!len, "Error: Expected len to be 0, but was %d instead.\n", len);

        hr = IUriBuilder_GetUserName(builder, NULL, NULL);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetUserName returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        received = (void*) 0xdeadbeef;
        hr = IUriBuilder_GetUserName(builder, NULL, &received);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetUserName returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        ok(!received, "Error: Expected received to be NULL, but was %p instead.\n", received);
        len = -1;
        hr = IUriBuilder_GetUserName(builder, &len, NULL);
        ok(hr == E_POINTER, "Error: IUriBuilder_GetUserName returned 0x%08x, expected 0x%08x.\n",
            hr, E_POINTER);
        ok(!len, "Error: Expected len to be 0, but was %d instead.\n", len);
    }
    if(builder) IUriBuilder_Release(builder);
}