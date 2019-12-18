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
typedef  int /*<<< orphan*/  LPOLESTR ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IROTData ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ CreateBindCtx (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ CreatePointerMoniker (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ CreateStreamOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ **,...) ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ E_NOINTERFACE ; 
 scalar_t__ E_NOTIMPL ; 
 scalar_t__ E_UNEXPECTED ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IROTData ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ IMoniker_BindToObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IMoniker_BindToStorage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IMoniker_GetDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IMoniker_GetTimeOfLastChange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IMoniker_Hash (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IMoniker_Inverse (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IMoniker_IsDirty (int /*<<< orphan*/ *) ; 
 scalar_t__ IMoniker_IsRunning (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IMoniker_IsSystemMoniker (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IMoniker_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IMoniker_Save (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ MKSYS_POINTERMONIKER ; 
 scalar_t__ PtrToUlong (int /*<<< orphan*/ *) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Test_ClassFactory ; 
 scalar_t__ cLocks ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  ok_more_than_one_lock () ; 
 int /*<<< orphan*/  ok_no_locks () ; 
 int /*<<< orphan*/  ok_ole_success (scalar_t__,...) ; 

__attribute__((used)) static void test_pointer_moniker(void)
{
    HRESULT hr;
    IMoniker *moniker;
    DWORD moniker_type;
    DWORD hash;
    IBindCtx *bindctx;
    FILETIME filetime;
    IMoniker *inverse;
    IUnknown *unknown;
    IStream *stream;
    IROTData *rotdata;
    LPOLESTR display_name;

    cLocks = 0;

    hr = CreatePointerMoniker((IUnknown *)&Test_ClassFactory, NULL);
    ok(hr == E_INVALIDARG, "CreatePointerMoniker(x, NULL) should have returned E_INVALIDARG instead of 0x%08x\n", hr);

    hr = CreatePointerMoniker((IUnknown *)&Test_ClassFactory, &moniker);
    ok_ole_success(hr, CreatePointerMoniker);
    if (!moniker) return;

    ok_more_than_one_lock();

    /* Display Name */

    hr = CreateBindCtx(0, &bindctx);
    ok_ole_success(hr, CreateBindCtx);

    hr = IMoniker_GetDisplayName(moniker, bindctx, NULL, &display_name);
    ok(hr == E_NOTIMPL, "IMoniker_GetDisplayName should have returned E_NOTIMPL instead of 0x%08x\n", hr);

    IBindCtx_Release(bindctx);

    hr = IMoniker_IsDirty(moniker);
    ok(hr == S_FALSE, "IMoniker_IsDirty should return S_FALSE, not 0x%08x\n", hr);

    /* IROTData::GetComparisonData test */

    hr = IMoniker_QueryInterface(moniker, &IID_IROTData, (void **)&rotdata);
    ok(hr == E_NOINTERFACE, "IMoniker_QueryInterface(IID_IROTData) should have returned E_NOINTERFACE instead of 0x%08x\n", hr);

    /* Saving */

    hr = CreateStreamOnHGlobal(NULL, TRUE, &stream);
    ok_ole_success(hr, CreateStreamOnHGlobal);

    hr = IMoniker_Save(moniker, stream, TRUE);
    ok(hr == E_NOTIMPL, "IMoniker_Save should have returned E_NOTIMPL instead of 0x%08x\n", hr);

    IStream_Release(stream);

    /* Hashing */
    hr = IMoniker_Hash(moniker, &hash);
    ok_ole_success(hr, IMoniker_Hash);
    ok(hash == PtrToUlong(&Test_ClassFactory),
        "Hash value should have been 0x%08x, instead of 0x%08x\n",
        PtrToUlong(&Test_ClassFactory), hash);

    /* IsSystemMoniker test */
    hr = IMoniker_IsSystemMoniker(moniker, &moniker_type);
    ok_ole_success(hr, IMoniker_IsSystemMoniker);
    ok(moniker_type == MKSYS_POINTERMONIKER,
        "dwMkSys != MKSYS_POINTERMONIKER, instead was 0x%08x\n",
        moniker_type);

    hr = IMoniker_Inverse(moniker, &inverse);
    ok_ole_success(hr, IMoniker_Inverse);
    IMoniker_Release(inverse);

    hr = CreateBindCtx(0, &bindctx);
    ok_ole_success(hr, CreateBindCtx);

    /* IsRunning test */
    hr = IMoniker_IsRunning(moniker, bindctx, NULL, NULL);
    ok(hr == S_OK, "IMoniker_IsRunning should return S_OK, not 0x%08x\n", hr);

    hr = IMoniker_GetTimeOfLastChange(moniker, bindctx, NULL, &filetime);
    ok(hr == E_NOTIMPL, "IMoniker_GetTimeOfLastChange should return E_NOTIMPL, not 0x%08x\n", hr);

    hr = IMoniker_BindToObject(moniker, bindctx, NULL, &IID_IUnknown, (void **)&unknown);
    ok_ole_success(hr, IMoniker_BindToObject);
    IUnknown_Release(unknown);

    hr = IMoniker_BindToStorage(moniker, bindctx, NULL, &IID_IUnknown, (void **)&unknown);
    ok_ole_success(hr, IMoniker_BindToStorage);
    IUnknown_Release(unknown);

    IMoniker_Release(moniker);

    ok_no_locks();

    hr = CreatePointerMoniker(NULL, &moniker);
    ok_ole_success(hr, CreatePointerMoniker);

    hr = IMoniker_BindToObject(moniker, bindctx, NULL, &IID_IUnknown, (void **)&unknown);
    ok(hr == E_UNEXPECTED, "IMoniker_BindToObject should have returned E_UNEXPECTED instead of 0x%08x\n", hr);

    hr = IMoniker_BindToStorage(moniker, bindctx, NULL, &IID_IUnknown, (void **)&unknown);
    ok(hr == E_UNEXPECTED, "IMoniker_BindToStorage should have returned E_UNEXPECTED instead of 0x%08x\n", hr);

    IBindCtx_Release(bindctx);

    IMoniker_Release(moniker);
}