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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetBindInfo ; 
 int /*<<< orphan*/  IInternetProtocol_Start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ITS_PROTOCOL ; 
 scalar_t__ MK_PROTOCOL ; 
 int /*<<< orphan*/  ReportData ; 
 int /*<<< orphan*/  ReportProgress_BEGINDOWNLOADDATA ; 
 int /*<<< orphan*/  ReportProgress_CACHEFILENAMEAVAILABLE ; 
 int /*<<< orphan*/  ReportProgress_DIRECTBIND ; 
 int /*<<< orphan*/  ReportProgress_MIMETYPEAVAILABLE ; 
 int /*<<< orphan*/  ReportProgress_SENDINGREQUEST ; 
 int /*<<< orphan*/  ReportResult ; 
 int /*<<< orphan*/  SET_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  bind_info ; 
 int /*<<< orphan*/  expect_hrResult ; 
 int /*<<< orphan*/  protocol_sink ; 
 scalar_t__ test_protocol ; 

__attribute__((used)) static HRESULT _protocol_start(unsigned line, IInternetProtocol *protocol, LPCWSTR url, BOOL expect_mime)
{
    HRESULT hres;

    SET_EXPECT(GetBindInfo);
    if(test_protocol == MK_PROTOCOL)
        SET_EXPECT(ReportProgress_DIRECTBIND);
    SET_EXPECT(ReportProgress_SENDINGREQUEST);
    if(expect_mime)
        SET_EXPECT(ReportProgress_MIMETYPEAVAILABLE);
    if(test_protocol == MK_PROTOCOL)
        SET_EXPECT(ReportProgress_CACHEFILENAMEAVAILABLE);
    SET_EXPECT(ReportData);
    if(test_protocol == ITS_PROTOCOL)
        SET_EXPECT(ReportProgress_BEGINDOWNLOADDATA);
    SET_EXPECT(ReportResult);
    expect_hrResult = S_OK;

    hres = IInternetProtocol_Start(protocol, url, &protocol_sink, &bind_info, 0, 0);

    if(FAILED(hres)) {
        SET_CALLED(GetBindInfo);
        if(test_protocol == MK_PROTOCOL)
            SET_CALLED(ReportProgress_DIRECTBIND);
        SET_CALLED(ReportProgress_SENDINGREQUEST);
        if(expect_mime)
            SET_CALLED(ReportProgress_MIMETYPEAVAILABLE);
        if(test_protocol == MK_PROTOCOL)
            SET_EXPECT(ReportProgress_CACHEFILENAMEAVAILABLE);
        SET_CALLED(ReportData);
        if(test_protocol == ITS_PROTOCOL)
            SET_CALLED(ReportProgress_BEGINDOWNLOADDATA);
        SET_CALLED(ReportResult);
    }else {
        CHECK_CALLED(GetBindInfo);
        if(test_protocol == MK_PROTOCOL)
            SET_CALLED(ReportProgress_DIRECTBIND);
        CHECK_CALLED(ReportProgress_SENDINGREQUEST);
        if(expect_mime)
            CHECK_CALLED(ReportProgress_MIMETYPEAVAILABLE);
        if(test_protocol == MK_PROTOCOL)
            SET_EXPECT(ReportProgress_CACHEFILENAMEAVAILABLE);
        CHECK_CALLED(ReportData);
        if(test_protocol == ITS_PROTOCOL)
            CHECK_CALLED(ReportProgress_BEGINDOWNLOADDATA);
        CHECK_CALLED(ReportResult);
    }

    return hres;
}