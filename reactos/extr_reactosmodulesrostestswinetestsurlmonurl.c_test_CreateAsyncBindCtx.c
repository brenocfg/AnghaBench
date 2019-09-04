#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bindopts ;
typedef  scalar_t__ ULONG ;
struct TYPE_3__ {int cbStruct; scalar_t__ grfFlags; int grfMode; int /*<<< orphan*/  dwTickCountDeadline; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IBindStatusCallback ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ BIND_OPTS ;

/* Variables and functions */
 scalar_t__ BIND_MAYBOTHERUSER ; 
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateAsyncBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_NOINTERFACE ; 
 int /*<<< orphan*/  IBindCtx_GetBindOptions (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  IBindCtx_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IBindCtx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAsyncBindCtx ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QueryInterface_IServiceProvider ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  bsc ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_CreateAsyncBindCtx(void)
{
    IBindCtx *bctx = (IBindCtx*)0x0ff00ff0;
    IUnknown *unk;
    HRESULT hres;
    ULONG ref;
    BIND_OPTS bindopts;

    hres = CreateAsyncBindCtx(0, NULL, NULL, &bctx);
    ok(hres == E_INVALIDARG, "CreateAsyncBindCtx failed. expected: E_INVALIDARG, got: %08x\n", hres);
    ok(bctx == (IBindCtx*)0x0ff00ff0, "bctx should not be changed\n");

    hres = CreateAsyncBindCtx(0, NULL, NULL, NULL);
    ok(hres == E_INVALIDARG, "CreateAsyncBindCtx failed. expected: E_INVALIDARG, got: %08x\n", hres);

    SET_EXPECT(QueryInterface_IServiceProvider);
    hres = CreateAsyncBindCtx(0, (IBindStatusCallback*)&bsc, NULL, &bctx);
    ok(hres == S_OK, "CreateAsyncBindCtx failed: %08x\n", hres);
    CHECK_CALLED(QueryInterface_IServiceProvider);

    bindopts.cbStruct = sizeof(bindopts);
    hres = IBindCtx_GetBindOptions(bctx, &bindopts);
    ok(hres == S_OK, "IBindCtx_GetBindOptions failed: %08x\n", hres);
    ok(bindopts.grfFlags == BIND_MAYBOTHERUSER,
                "bindopts.grfFlags = %08x, expected: BIND_MAYBOTHERUSER\n", bindopts.grfFlags);
    ok(bindopts.grfMode == (STGM_READWRITE | STGM_SHARE_EXCLUSIVE),
                "bindopts.grfMode = %08x, expected: STGM_READWRITE | STGM_SHARE_EXCLUSIVE\n",
                bindopts.grfMode);
    ok(bindopts.dwTickCountDeadline == 0,
                "bindopts.dwTickCountDeadline = %08x, expected: 0\n", bindopts.dwTickCountDeadline);

    hres = IBindCtx_QueryInterface(bctx, &IID_IAsyncBindCtx, (void**)&unk);
    ok(hres == E_NOINTERFACE, "QueryInterface(IID_IAsyncBindCtx) failed: %08x, expected E_NOINTERFACE\n", hres);
    if(SUCCEEDED(hres))
        IUnknown_Release(unk);

    ref = IBindCtx_Release(bctx);
    ok(ref == 0, "bctx should be destroyed here\n");
}