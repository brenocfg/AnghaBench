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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IBindStatusCallback ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ABOUT_TEST ; 
 int /*<<< orphan*/  BINDTEST_EMULATE ; 
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAR_CALLED (int /*<<< orphan*/ ) ; 
 scalar_t__ CreateAsyncBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ CreateURLMoniker (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GetBindInfo ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IStream ; 
 scalar_t__ IMoniker_BindToStorage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ MK_S_ASYNCHRONOUS ; 
 int /*<<< orphan*/  OnStartBinding ; 
 int /*<<< orphan*/  QueryInterface_IBindStatusCallbackEx ; 
 int /*<<< orphan*/  QueryInterface_IInternetProtocol ; 
 int /*<<< orphan*/  QueryInterface_IServiceProvider ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetPriority ; 
 int /*<<< orphan*/  Start ; 
 int /*<<< orphan*/  TYMED_ISTREAM ; 
 int /*<<< orphan*/  about_blankW ; 
 scalar_t__ binding_hres ; 
 int /*<<< orphan*/  bsc ; 
 int /*<<< orphan*/  init_bind_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_urlmon_protocol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  test_protocol ; 

__attribute__((used)) static void test_ReportResult(HRESULT exhres)
{
    IMoniker *mon = NULL;
    IBindCtx *bctx = NULL;
    IUnknown *unk = (void*)0xdeadbeef;
    HRESULT hres;

    init_bind_test(ABOUT_TEST, BINDTEST_EMULATE, TYMED_ISTREAM);
    binding_hres = exhres;

    hres = CreateURLMoniker(NULL, about_blankW, &mon);
    ok(hres == S_OK, "CreateURLMoniker failed: %08x\n", hres);

    SET_EXPECT(QueryInterface_IServiceProvider);
    hres = CreateAsyncBindCtx(0, (IBindStatusCallback*)&bsc, NULL, &bctx);
    ok(hres == S_OK, "CreateAsyncBindCtx failed: %08x\n\n", hres);
    CHECK_CALLED(QueryInterface_IServiceProvider);

    SET_EXPECT(QueryInterface_IBindStatusCallbackEx);
    SET_EXPECT(GetBindInfo);
    SET_EXPECT(QueryInterface_IInternetProtocol);
    SET_EXPECT(OnStartBinding);
    if(is_urlmon_protocol(test_protocol))
        SET_EXPECT(SetPriority);
    SET_EXPECT(Start);

    hres = IMoniker_BindToStorage(mon, bctx, NULL, &IID_IStream, (void**)&unk);
    if(SUCCEEDED(exhres))
        ok(hres == S_OK || hres == MK_S_ASYNCHRONOUS, "BindToStorage failed: %08x\n", hres);
    else
        ok(hres == exhres || hres == MK_S_ASYNCHRONOUS,
           "BindToStorage failed: %08x, expected %08x or MK_S_ASYNCHRONOUS\n", hres, exhres);

    CLEAR_CALLED(QueryInterface_IBindStatusCallbackEx); /* IE 8 */
    CHECK_CALLED(GetBindInfo);
    CHECK_CALLED(QueryInterface_IInternetProtocol);
    CHECK_CALLED(OnStartBinding);
    if(is_urlmon_protocol(test_protocol))
        CLEAR_CALLED(SetPriority); /* Not called by IE11 */
    CHECK_CALLED(Start);

    ok(unk == NULL, "unk=%p\n", unk);

    IBindCtx_Release(bctx);
    IMoniker_Release(mon);
}