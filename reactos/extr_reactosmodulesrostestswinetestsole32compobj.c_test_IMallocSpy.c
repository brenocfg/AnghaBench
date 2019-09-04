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
typedef  int /*<<< orphan*/  IMalloc ;
typedef  int /*<<< orphan*/ * HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/ * CO_E_OBJISREG ; 
 int /*<<< orphan*/ * CO_E_OBJNOTREG ; 
 int /*<<< orphan*/ * CoGetMalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * CoRegisterMallocSpy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CoRevokeMallocSpy () ; 
 int /*<<< orphan*/ * E_INVALIDARG ; 
 int /*<<< orphan*/  IMalloc_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMalloc_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEMCTX_TASK ; 
 int /*<<< orphan*/ * S_OK ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testspy ; 

__attribute__((used)) static void test_IMallocSpy(void)
{
    IMalloc *imalloc;
    HRESULT hr;

    hr = CoRegisterMallocSpy(NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = CoRevokeMallocSpy();
    ok(hr == CO_E_OBJNOTREG, "got 0x%08x\n", hr);

    hr = CoRegisterMallocSpy(&testspy);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = CoRegisterMallocSpy(NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = CoRegisterMallocSpy(&testspy);
    ok(hr == CO_E_OBJISREG, "got 0x%08x\n", hr);

    imalloc = NULL;
    hr = CoGetMalloc(MEMCTX_TASK, &imalloc);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(imalloc != NULL, "got %p\n", imalloc);

    IMalloc_Free(imalloc, NULL);

    IMalloc_Release(imalloc);

    hr = CoRevokeMallocSpy();
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = CoRevokeMallocSpy();
    ok(hr == CO_E_OBJNOTREG, "got 0x%08x\n", hr);
}