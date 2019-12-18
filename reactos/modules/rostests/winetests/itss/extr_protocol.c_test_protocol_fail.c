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
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IInternetProtocol ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetBindInfo ; 
 int /*<<< orphan*/  IInternetProtocol_Start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportResult ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bind_info ; 
 int /*<<< orphan*/  expect_hrResult ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  protocol_sink ; 

__attribute__((used)) static void test_protocol_fail(IInternetProtocol *protocol, LPCWSTR url, HRESULT expected_hres)
{
    HRESULT hres;

    SET_EXPECT(GetBindInfo);
    SET_EXPECT(ReportResult);

    expect_hrResult = expected_hres;
    hres = IInternetProtocol_Start(protocol, url, &protocol_sink, &bind_info, 0, 0);
    ok(hres == expected_hres, "expected: %08x got: %08x\n", expected_hres, hres);

    CHECK_CALLED(GetBindInfo);
    CHECK_CALLED(ReportResult);
}