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
typedef  int /*<<< orphan*/  clsid ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  int HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLSID_ClassMoniker ; 
 int /*<<< orphan*/  CreateBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int E_INVALIDARG ; 
 int E_NOTIMPL ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IQueryCancelAutoPlay ; 
 int IMoniker_BindToObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int IMoniker_GetClassID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IMoniker_IsSystemMoniker (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 int IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MKSYS_CLASSMONIKER ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 int S_OK ; 
 int /*<<< orphan*/  autoplay_BindToObject ; 
 int /*<<< orphan*/  autoplay_GetClassObject ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int pSHCreateQueryCancelAutoPlayMoniker (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  test_moniker ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_SHCreateQueryCancelAutoPlayMoniker(void)
{
    IBindCtx *ctxt;
    IMoniker *mon;
    IUnknown *unk;
    CLSID clsid;
    HRESULT hr;
    DWORD sys;

    if (!pSHCreateQueryCancelAutoPlayMoniker)
    {
        win_skip("SHCreateQueryCancelAutoPlayMoniker is not available, skipping tests.\n");
        return;
    }

    hr = pSHCreateQueryCancelAutoPlayMoniker(NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = pSHCreateQueryCancelAutoPlayMoniker(&mon);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    sys = -1;
    hr = IMoniker_IsSystemMoniker(mon, &sys);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(sys == MKSYS_CLASSMONIKER, "got %d\n", sys);

    memset(&clsid, 0, sizeof(clsid));
    hr = IMoniker_GetClassID(mon, &clsid);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(IsEqualGUID(&clsid, &CLSID_ClassMoniker), "got %s\n", wine_dbgstr_guid(&clsid));

    /* extract used CLSID that implements this hook */
    SET_EXPECT(autoplay_BindToObject);
    SET_EXPECT(autoplay_GetClassObject);

    CreateBindCtx(0, &ctxt);
    hr = IMoniker_BindToObject(mon, ctxt, &test_moniker, &IID_IQueryCancelAutoPlay, (void**)&unk);
    ok(hr == E_NOTIMPL, "got 0x%08x\n", hr);
    IBindCtx_Release(ctxt);

    CHECK_CALLED(autoplay_BindToObject);
    CHECK_CALLED(autoplay_GetClassObject);

    IMoniker_Release(mon);
}