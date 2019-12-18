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
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  IInternetProtocolEx ;
typedef  int /*<<< orphan*/  IInternetProtocol ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int BINDF_FROMURLMON ; 
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAR_CALLED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetBindInfo ; 
 scalar_t__ IInternetProtocolEx_StartEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IInternetProtocol_Start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ INET_E_RESOURCE_NOT_FOUND ; 
 int /*<<< orphan*/  ReportData ; 
 int /*<<< orphan*/  ReportProgress_CACHEFILENAMEAVAILABLE ; 
 int /*<<< orphan*/  ReportProgress_DIRECTBIND ; 
 int /*<<< orphan*/  ReportProgress_MIMETYPEAVAILABLE ; 
 int /*<<< orphan*/  ReportProgress_SENDINGREQUEST ; 
 int /*<<< orphan*/  ReportProgress_VERIFIEDMIMETYPEAVAILABLE ; 
 int /*<<< orphan*/  ReportResult ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  bind_info ; 
 int bindf ; 
 scalar_t__ expect_hrResult ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  protocol_sink ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static BOOL file_protocol_start(IInternetProtocol *protocol, LPCWSTR url,
        IInternetProtocolEx *protocolex, IUri *uri, BOOL is_first)
{
    HRESULT hres;

    SET_EXPECT(GetBindInfo);
    if(!(bindf & BINDF_FROMURLMON))
       SET_EXPECT(ReportProgress_DIRECTBIND);
    if(is_first) {
        SET_EXPECT(ReportProgress_SENDINGREQUEST);
        SET_EXPECT(ReportProgress_CACHEFILENAMEAVAILABLE);
        if(bindf & BINDF_FROMURLMON)
            SET_EXPECT(ReportProgress_VERIFIEDMIMETYPEAVAILABLE);
        else
            SET_EXPECT(ReportProgress_MIMETYPEAVAILABLE);
    }
    SET_EXPECT(ReportData);
    if(is_first)
        SET_EXPECT(ReportResult);

    expect_hrResult = S_OK;

    if(protocolex) {
        hres = IInternetProtocolEx_StartEx(protocolex, uri, &protocol_sink, &bind_info, 0, 0);
        ok(hres == S_OK, "StartEx failed: %08x\n", hres);
    }else {
        hres = IInternetProtocol_Start(protocol, url, &protocol_sink, &bind_info, 0, 0);
        if(hres == INET_E_RESOURCE_NOT_FOUND) {
            win_skip("Start failed\n");
            return FALSE;
        }
        ok(hres == S_OK, "Start failed: %08x\n", hres);
    }

    CHECK_CALLED(GetBindInfo);
    if(!(bindf & BINDF_FROMURLMON))
        CLEAR_CALLED(ReportProgress_DIRECTBIND); /* Not called by IE10 */
    if(is_first) {
        CHECK_CALLED(ReportProgress_SENDINGREQUEST);
        CHECK_CALLED(ReportProgress_CACHEFILENAMEAVAILABLE);
        if(bindf & BINDF_FROMURLMON)
            CHECK_CALLED(ReportProgress_VERIFIEDMIMETYPEAVAILABLE);
        else
            CHECK_CALLED(ReportProgress_MIMETYPEAVAILABLE);
    }
    CHECK_CALLED(ReportData);
    if(is_first)
        CHECK_CALLED(ReportResult);

    return TRUE;
}