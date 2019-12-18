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
typedef  int /*<<< orphan*/  IXMLHttpRequest ;
typedef  int /*<<< orphan*/  ISupportErrorInfo ;
typedef  int /*<<< orphan*/  IServerXMLHTTPRequest ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT_REF (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IID_ISupportErrorInfo ; 
 scalar_t__ IServerXMLHTTPRequest_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IServerXMLHTTPRequest_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISupportErrorInfo_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLHttpRequest_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IXMLHttpRequest_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * create_server_xhr () ; 
 int /*<<< orphan*/ * create_xhr () ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_supporterrorinfo(void)
{
    HRESULT hr;
    IXMLHttpRequest *xhr;
    IServerXMLHTTPRequest *server_xhr;
    ISupportErrorInfo *errorinfo, *errorinfo2;

    xhr = create_xhr();

    EXPECT_REF(xhr, 1);
    hr = IXMLHttpRequest_QueryInterface(xhr, &IID_ISupportErrorInfo, (void **)&errorinfo);
    ok(hr == S_OK, "Failed to get ISupportErrorInfo, hr %#x.\n", hr);
    EXPECT_REF(xhr, 2);

    hr = IXMLHttpRequest_QueryInterface(xhr, &IID_ISupportErrorInfo, (void **)&errorinfo2);
    ok(hr == S_OK, "Failed to get ISupportErrorInfo, hr %#x.\n", hr);
    ok(errorinfo == errorinfo2, "Unexpected error info instance.\n");
    EXPECT_REF(xhr, 3);

    ISupportErrorInfo_Release(errorinfo2);
    ISupportErrorInfo_Release(errorinfo);

    IXMLHttpRequest_Release(xhr);

    /* ServerXMLHTTP */
    server_xhr = create_server_xhr();

    EXPECT_REF(server_xhr, 1);
    hr = IServerXMLHTTPRequest_QueryInterface(server_xhr, &IID_ISupportErrorInfo, (void **)&errorinfo);
    ok(hr == S_OK, "Failed to get ISupportErrorInfo, hr %#x.\n", hr);
    EXPECT_REF(server_xhr, 2);

    hr = IServerXMLHTTPRequest_QueryInterface(server_xhr, &IID_ISupportErrorInfo, (void **)&errorinfo2);
    ok(hr == S_OK, "Failed to get ISupportErrorInfo, hr %#x.\n", hr);
    ok(errorinfo == errorinfo2, "Unexpected error info instance.\n");
    EXPECT_REF(server_xhr, 3);

    ISupportErrorInfo_Release(errorinfo2);
    ISupportErrorInfo_Release(errorinfo);

    IServerXMLHTTPRequest_Release(server_xhr);
}