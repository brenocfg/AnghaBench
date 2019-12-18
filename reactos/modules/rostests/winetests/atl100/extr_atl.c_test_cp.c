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
typedef  int HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int AtlAdvise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int AtlUnadvise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CLSID_Test ; 
 int /*<<< orphan*/  ConnectionPointContainer ; 
 int E_INVALIDARG ; 
 int S_OK ; 
 int advise_cnt ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_cp(void)
{
    DWORD cookie = 0;
    HRESULT hres;

    hres = AtlAdvise(NULL, (IUnknown*)0xdeed0000, &CLSID_Test, &cookie);
    ok(hres == E_INVALIDARG, "expect E_INVALIDARG, returned %08x\n", hres);

    hres = AtlUnadvise(NULL, &CLSID_Test, 0xdeadbeef);
    ok(hres == E_INVALIDARG, "expect E_INVALIDARG, returned %08x\n", hres);

    hres = AtlAdvise((IUnknown*)&ConnectionPointContainer, (IUnknown*)0xdead0000, &CLSID_Test, &cookie);
    ok(hres == S_OK, "AtlAdvise failed: %08x\n", hres);
    ok(cookie == 0xdeadbeef, "cookie = %x\n", cookie);
    ok(advise_cnt == 1, "advise_cnt = %d\n", advise_cnt);

    hres = AtlUnadvise((IUnknown*)&ConnectionPointContainer, &CLSID_Test, 0xdeadbeef);
    ok(hres == S_OK, "AtlUnadvise failed: %08x\n", hres);
    ok(!advise_cnt, "advise_cnt = %d\n", advise_cnt);
}