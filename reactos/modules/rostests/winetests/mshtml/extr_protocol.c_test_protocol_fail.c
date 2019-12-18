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
typedef  int HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int FACILITY_WIN32 ; 
 int /*<<< orphan*/  GetBindInfo ; 
 int IInternetProtocol_Start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportResult ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bind_info ; 
 int expect_hrResult ; 
 scalar_t__ expect_hr_win32err ; 
 int /*<<< orphan*/  ok (int,char*,int,int) ; 
 int /*<<< orphan*/  protocol_sink ; 

__attribute__((used)) static void test_protocol_fail(IInternetProtocol *protocol, LPCWSTR url, HRESULT expected_hres,
        BOOL expect_win32err)
{
    HRESULT hres;

    SET_EXPECT(GetBindInfo);
    SET_EXPECT(ReportResult);

    expect_hrResult = expected_hres;
    expect_hr_win32err = expect_win32err;
    hres = IInternetProtocol_Start(protocol, url, &protocol_sink, &bind_info, 0, 0);
    if(expect_win32err)
        ok((hres&0xffff0000) == ((FACILITY_WIN32 << 16)|0x80000000) || hres == expect_hrResult,
                "expected win32 err or %08x got: %08x\n", expected_hres, hres);
    else
        ok(hres == expect_hrResult, "expected: %08x got: %08x\n", expect_hrResult, hres);

    CHECK_CALLED(GetBindInfo);
    CHECK_CALLED(ReportResult);
}