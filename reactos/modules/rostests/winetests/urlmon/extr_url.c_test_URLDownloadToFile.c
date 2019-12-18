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
typedef  int /*<<< orphan*/  IBindStatusCallback ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int BINDTEST_EMULATE ; 
 int BINDTEST_FILEDWLAPI ; 
 int /*<<< orphan*/  BeginningTransaction ; 
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAR_CALLED (int /*<<< orphan*/ ) ; 
 int DeleteFileA (int /*<<< orphan*/ ) ; 
 scalar_t__ FILE_TEST ; 
 int /*<<< orphan*/  GetBindInfo ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetRootSecurityId ; 
 scalar_t__ HTTPS_TEST ; 
 scalar_t__ HTTP_TEST ; 
 int /*<<< orphan*/  OnProgress_BEGINDOWNLOADDATA ; 
 int /*<<< orphan*/  OnProgress_CACHEFILENAMEAVAILABLE ; 
 int /*<<< orphan*/  OnProgress_CONNECTING ; 
 int /*<<< orphan*/  OnProgress_DOWNLOADINGDATA ; 
 int /*<<< orphan*/  OnProgress_ENDDOWNLOADDATA ; 
 int /*<<< orphan*/  OnProgress_MIMETYPEAVAILABLE ; 
 int /*<<< orphan*/  OnProgress_SENDINGREQUEST ; 
 int /*<<< orphan*/  OnResponse ; 
 int /*<<< orphan*/  OnStartBinding ; 
 int /*<<< orphan*/  OnStopBinding ; 
 int /*<<< orphan*/  QueryInterface_IHttpNegotiate ; 
 int /*<<< orphan*/  QueryInterface_IHttpNegotiate2 ; 
 int /*<<< orphan*/  QueryInterface_IInternetProtocol ; 
 int /*<<< orphan*/  QueryInterface_IServiceProvider ; 
 int /*<<< orphan*/  QueryInterface_IWindowForBindingUI ; 
 int /*<<< orphan*/  QueryService_IInternetProtocol ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetPriority ; 
 int /*<<< orphan*/  Start ; 
 int /*<<< orphan*/  TYMED_FILE ; 
 scalar_t__ URLDownloadToFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockRequest ; 
 int /*<<< orphan*/  bsc ; 
 int /*<<< orphan*/  current_url ; 
 int /*<<< orphan*/  dwl_htmlA ; 
 int /*<<< orphan*/  dwl_htmlW ; 
 scalar_t__ emulate_protocol ; 
 scalar_t__ have_IHttpNegotiate2 ; 
 int /*<<< orphan*/  init_bind_test (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_urlmon_protocol (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ test_protocol ; 

__attribute__((used)) static void test_URLDownloadToFile(DWORD prot, BOOL emul)
{
    BOOL res;
    HRESULT hres;

    init_bind_test(prot, BINDTEST_FILEDWLAPI | (emul ? BINDTEST_EMULATE : 0), TYMED_FILE);

    SET_EXPECT(GetBindInfo);
    SET_EXPECT(QueryInterface_IInternetProtocol);
    SET_EXPECT(QueryInterface_IServiceProvider);
    if(!emulate_protocol)
        SET_EXPECT(QueryService_IInternetProtocol);
    SET_EXPECT(OnStartBinding);
    if(emulate_protocol) {
        if(is_urlmon_protocol(test_protocol))
            SET_EXPECT(SetPriority);
        SET_EXPECT(Start);
        SET_EXPECT(UnlockRequest);
    }else {
        if(test_protocol == HTTP_TEST || test_protocol == HTTPS_TEST) {
            SET_EXPECT(QueryInterface_IHttpNegotiate);
            SET_EXPECT(BeginningTransaction);
            SET_EXPECT(QueryInterface_IHttpNegotiate2);
            SET_EXPECT(GetRootSecurityId);
            SET_EXPECT(QueryInterface_IWindowForBindingUI);
            SET_EXPECT(OnProgress_CONNECTING);
        }
        if(test_protocol == HTTP_TEST || test_protocol == HTTPS_TEST || test_protocol == FILE_TEST)
            SET_EXPECT(OnProgress_SENDINGREQUEST);
        if(test_protocol == HTTP_TEST || test_protocol == HTTPS_TEST) {
            SET_EXPECT(QueryInterface_IHttpNegotiate);
            SET_EXPECT(OnResponse);
        }
        SET_EXPECT(OnProgress_MIMETYPEAVAILABLE);
        SET_EXPECT(OnProgress_BEGINDOWNLOADDATA);
        if(test_protocol == FILE_TEST)
            SET_EXPECT(OnProgress_CACHEFILENAMEAVAILABLE);
        if(test_protocol == HTTP_TEST || test_protocol == HTTPS_TEST)
            SET_EXPECT(OnProgress_DOWNLOADINGDATA);
        SET_EXPECT(OnProgress_ENDDOWNLOADDATA);
        SET_EXPECT(OnStopBinding);
    }

    hres = URLDownloadToFileW(NULL, current_url, dwl_htmlW, 0, (IBindStatusCallback*)&bsc);
    ok(hres == S_OK, "URLDownloadToFile failed: %08x\n", hres);

    CHECK_CALLED(GetBindInfo);
    CHECK_CALLED(QueryInterface_IInternetProtocol);
    if(!emulate_protocol) {
        CHECK_CALLED(QueryInterface_IServiceProvider);
        CHECK_CALLED(QueryService_IInternetProtocol);
    }else {
        CLEAR_CALLED(QueryInterface_IServiceProvider);
    }
    CHECK_CALLED(OnStartBinding);
    if(emulate_protocol) {
        if(is_urlmon_protocol(test_protocol))
            CLEAR_CALLED(SetPriority); /* Not called by IE11 */
        CHECK_CALLED(Start);
        CHECK_CALLED(UnlockRequest);
    }else {
        if(test_protocol == HTTP_TEST || test_protocol == HTTPS_TEST) {
            CHECK_CALLED(QueryInterface_IHttpNegotiate);
            CHECK_CALLED(BeginningTransaction);
            if (have_IHttpNegotiate2)
            {
                CHECK_CALLED(QueryInterface_IHttpNegotiate2);
                CHECK_CALLED(GetRootSecurityId);
            }
            CLEAR_CALLED(QueryInterface_IWindowForBindingUI);
            CLEAR_CALLED(OnProgress_CONNECTING);
        }
        if(test_protocol == FILE_TEST)
            CHECK_CALLED(OnProgress_SENDINGREQUEST);
        else if(test_protocol == HTTP_TEST || test_protocol == HTTPS_TEST)
            CLEAR_CALLED(OnProgress_SENDINGREQUEST); /* not called by IE7 */
        if(test_protocol == HTTP_TEST || test_protocol == HTTPS_TEST) {
            CLEAR_CALLED(QueryInterface_IHttpNegotiate);
            CHECK_CALLED(OnResponse);
        }
        CHECK_CALLED(OnProgress_MIMETYPEAVAILABLE);
        CHECK_CALLED(OnProgress_BEGINDOWNLOADDATA);
        if(test_protocol == FILE_TEST)
            CHECK_CALLED(OnProgress_CACHEFILENAMEAVAILABLE);
        if(test_protocol == HTTP_TEST || test_protocol == HTTPS_TEST)
            CLEAR_CALLED(OnProgress_DOWNLOADINGDATA);
        CHECK_CALLED(OnProgress_ENDDOWNLOADDATA);
        CHECK_CALLED(OnStopBinding);
    }

    res = DeleteFileA(dwl_htmlA);
    ok(res, "DeleteFile failed: %u\n", GetLastError());

    if(prot != FILE_TEST || emul)
        return;

    hres = URLDownloadToFileW(NULL, current_url, dwl_htmlW, 0, NULL);
    ok(hres == S_OK, "URLDownloadToFile failed: %08x\n", hres);

    res = DeleteFileA(dwl_htmlA);
    ok(res, "DeleteFile failed: %u\n", GetLastError());
}