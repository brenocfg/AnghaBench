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
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ CreateURLMoniker (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IStream ; 
 scalar_t__ IMoniker_BindToStorage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ INET_E_DATA_NOT_AVAILABLE ; 
 scalar_t__ MK_E_SYNTAX ; 
 int /*<<< orphan*/  S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  about_blankW ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pCreateAsyncBindCtxEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_ReportResult (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_BindToStorage_fail(void)
{
    IMoniker *mon = NULL;
    IBindCtx *bctx = NULL;
    IUnknown *unk;
    HRESULT hres;

    hres = CreateURLMoniker(NULL, about_blankW, &mon);
    ok(hres == S_OK, "CreateURLMoniker failed: %08x\n", hres);
    if(FAILED(hres))
        return;

    hres = pCreateAsyncBindCtxEx(NULL, 0, NULL, NULL, &bctx, 0);
    ok(hres == S_OK, "CreateAsyncBindCtxEx failed: %08x\n", hres);

    unk = (void*)0xdeadbeef;
    hres = IMoniker_BindToStorage(mon, bctx, NULL, &IID_IStream, (void**)&unk);
    ok(hres == MK_E_SYNTAX || hres == INET_E_DATA_NOT_AVAILABLE,
       "hres=%08x, expected MK_E_SYNTAX or INET_E_DATA_NOT_AVAILABLE\n", hres);
    ok(unk == NULL, "got %p\n", unk);

    IBindCtx_Release(bctx);

    IMoniker_Release(mon);

    test_ReportResult(E_NOTIMPL);
    test_ReportResult(S_FALSE);
}