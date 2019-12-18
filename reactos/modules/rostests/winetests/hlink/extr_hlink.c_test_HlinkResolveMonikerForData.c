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
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  BindStatusCallback ; 
 int /*<<< orphan*/  BindToStorage ; 
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GetDisplayName ; 
 scalar_t__ HlinkResolveMonikerForData (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsSystemMoniker ; 
 int /*<<< orphan*/  Moniker ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * _bctx ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_HlinkResolveMonikerForData(void)
{
    IBindCtx *bctx;
    HRESULT hres;

    CreateBindCtx(0, &bctx);
    _bctx = bctx;

    SET_EXPECT(IsSystemMoniker);
    SET_EXPECT(GetDisplayName);
    SET_EXPECT(BindToStorage);

    hres = HlinkResolveMonikerForData(&Moniker, 0, bctx, 0, NULL, &BindStatusCallback, NULL);
    ok(hres == S_OK, "HlinkResolveMonikerForData failed: %08x\n", hres);

    CHECK_CALLED(IsSystemMoniker);
    CHECK_CALLED(GetDisplayName);
    CHECK_CALLED(BindToStorage);

    IBindCtx_Release(bctx);
    _bctx = NULL;
}