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
 int /*<<< orphan*/  CreateBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IsValidURL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  wszHttpWineHQ ; 

__attribute__((used)) static void test_IsValidURL(void)
{
    HRESULT hr;
    IBindCtx *bctx = NULL;

    hr = IsValidURL(NULL, 0, 0);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %08x\n", hr);

    hr = IsValidURL(NULL, wszHttpWineHQ, 0);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    CreateBindCtx(0, &bctx);

    hr = IsValidURL(bctx, wszHttpWineHQ, 0);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    IBindCtx_Release(bctx);
}