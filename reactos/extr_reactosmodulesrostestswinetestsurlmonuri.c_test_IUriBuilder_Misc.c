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
typedef  int /*<<< orphan*/  IUriBuilder ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IUriBuilder_GetPort (int /*<<< orphan*/ *,scalar_t__*,int*) ; 
 int /*<<< orphan*/  IUriBuilder_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  http_urlW ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  pCreateIUriBuilder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pCreateUri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void test_IUriBuilder_Misc(void) {
    HRESULT hr;
    IUri *uri;

    hr = pCreateUri(http_urlW, 0, 0, &uri);
    if(SUCCEEDED(hr)) {
        IUriBuilder *builder;

        hr = pCreateIUriBuilder(uri, 0, 0, &builder);
        ok(hr == S_OK, "Error: CreateIUriBuilder returned 0x%08x, expected 0x%08x.\n", hr, S_OK);
        if(SUCCEEDED(hr)) {
            BOOL has = -1;
            DWORD port = -1;

            hr = IUriBuilder_GetPort(builder, &has, &port);
            ok(hr == S_OK, "Error: IUriBuilder_GetPort returned 0x%08x, expected 0x%08x.\n", hr, S_OK);
            if(SUCCEEDED(hr)) {
                /* 'has' will be set to FALSE, even though uri had a port. */
                ok(has == FALSE, "Error: Expected 'has' to be FALSE, was %d instead.\n", has);
                /* Still sets 'port' to 80. */
                ok(port == 80, "Error: Expected the port to be 80, but, was %d instead.\n", port);
            }
        }
        if(builder) IUriBuilder_Release(builder);
    }
    if(uri) IUri_Release(uri);
}