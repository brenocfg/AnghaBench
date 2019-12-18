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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IHlinkBrowseContext ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ CreateItemMoniker (char*,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HlinkCreateBrowseContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IHlinkBrowseContext_GetObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IHlinkBrowseContext_Register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHlinkBrowseContext_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHlinkBrowseContext_Revoke (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IHlinkBrowseContext ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ MK_E_UNAVAILABLE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  Unknown ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_GetObject(void)
{
    IHlinkBrowseContext *bc;
    IMoniker *dummy;
    IUnknown *unk;
    WCHAR one[] = {'1',0};
    WCHAR five[] = {'5',0};
    DWORD cookie;
    HRESULT hres;

    hres = CreateItemMoniker(one, five, &dummy);
    ok(hres == S_OK, "CreateItemMoniker() failed: 0x%08x\n", hres);

    hres = HlinkCreateBrowseContext(NULL, &IID_IHlinkBrowseContext, (void **)&bc);
    ok(hres == S_OK, "HlinkCreateBrowseContext() failed: 0x%08x\n", hres);

    hres = IHlinkBrowseContext_GetObject(bc, dummy, FALSE, &unk);
    ok(hres == MK_E_UNAVAILABLE, "expected MK_E_UNAVAILABLE, got 0x%08x\n", hres);

    hres = IHlinkBrowseContext_Register(bc, 0, &Unknown, dummy, &cookie);
    ok(hres == S_OK, "Register() failed: 0x%08x\n", hres);

    hres = IHlinkBrowseContext_GetObject(bc, dummy, FALSE, &unk);
    ok(hres == S_OK, "GetObject() failed: 0x%08x\n", hres);
    ok(unk == &Unknown, "wrong object returned\n");

    hres = IHlinkBrowseContext_Revoke(bc, cookie);
    ok(hres == S_OK, "Revoke() failed: 0x%08x\n", hres);

    hres = IHlinkBrowseContext_GetObject(bc, dummy, FALSE, &unk);
    ok(hres == MK_E_UNAVAILABLE, "expected MK_E_UNAVAILABLE, got 0x%08x\n", hres);

    IHlinkBrowseContext_Release(bc);
    IMoniker_Release(dummy);
}