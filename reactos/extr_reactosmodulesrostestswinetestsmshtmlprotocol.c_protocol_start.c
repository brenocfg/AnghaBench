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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IInternetProtocol ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetBindInfo ; 
 scalar_t__ IInternetProtocol_Start (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportData ; 
 int /*<<< orphan*/  ReportProgress ; 
 int /*<<< orphan*/  ReportResult ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  bind_info ; 
 scalar_t__ expect_hrResult ; 
 int /*<<< orphan*/  expect_hr_win32err ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  protocol_sink ; 

__attribute__((used)) static void protocol_start(IInternetProtocol *protocol, const WCHAR *url)
{
    HRESULT hres;

    SET_EXPECT(GetBindInfo);
    SET_EXPECT(ReportResult);
    SET_EXPECT(ReportProgress);
    SET_EXPECT(ReportData);
    expect_hrResult = S_OK;
    expect_hr_win32err = FALSE;

    hres = IInternetProtocol_Start(protocol, url, &protocol_sink, &bind_info, 0, 0);
    ok(hres == S_OK, "Start failed: %08x\n", hres);

    CHECK_CALLED(GetBindInfo);
    CHECK_CALLED(ReportProgress);
    CHECK_CALLED(ReportData);
    CHECK_CALLED(ReportResult);
}