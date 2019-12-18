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
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/ * HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * E_INVALIDARG ; 
 int /*<<< orphan*/ * E_NOTIMPL ; 
 int HLSR_HISTORYFOLDER ; 
 int HLSR_HOME ; 
 int HLSR_SEARCHPAGE ; 
 int /*<<< orphan*/ * HlinkGetSpecialReference (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_special_reference(void)
{
    LPWSTR ref;
    HRESULT hres;

    hres = HlinkGetSpecialReference(HLSR_HOME, &ref);
    ok(hres == S_OK, "HlinkGetSpecialReference(HLSR_HOME) failed: %08x\n", hres);
    ok(ref != NULL, "ref == NULL\n");
    CoTaskMemFree(ref);

    hres = HlinkGetSpecialReference(HLSR_SEARCHPAGE, &ref);
    ok(hres == S_OK, "HlinkGetSpecialReference(HLSR_SEARCHPAGE) failed: %08x\n", hres);
    ok(ref != NULL, "ref == NULL\n");
    CoTaskMemFree(ref);

    ref = (void*)0xdeadbeef;
    hres = HlinkGetSpecialReference(HLSR_HISTORYFOLDER, &ref);
    ok(hres == E_NOTIMPL, "HlinkGetSpecialReference(HLSR_HISTORYFOLDER) failed: %08x\n", hres);
    ok(ref == NULL, "ref=%p\n", ref);

    ref = (void*)0xdeadbeef;
    hres = HlinkGetSpecialReference(4, &ref);
    ok(hres == E_INVALIDARG, "HlinkGetSpecialReference(HLSR_HISTORYFOLDER) failed: %08x\n", hres);
    ok(ref == NULL, "ref=%p\n", ref);
}