#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sfvc ;
typedef  int /*<<< orphan*/ * ULONG ;
struct TYPE_4__ {int cbSize; int /*<<< orphan*/ * pshf; } ;
typedef  TYPE_1__ SFV_CREATE ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IShellView ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int /*<<< orphan*/ * HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/ * E_INVALIDARG ; 
 int /*<<< orphan*/ * E_UNEXPECTED ; 
 int /*<<< orphan*/  IID_CDefView ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IShellView_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * IShellView_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SHCreateShellFolderView (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * SHGetDesktopFolder (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * S_OK ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_SHCreateShellFolderView(void)
{
    IShellFolder *desktop;
    IShellView *psv;
    SFV_CREATE sfvc;
    ULONG refCount;
    IUnknown *unk;
    HRESULT hr;

    hr = SHGetDesktopFolder(&desktop);
    ok(hr == S_OK, "got (0x%08x)\n", hr);

    if (0)
    {
        /* crash on win7 */
        SHCreateShellFolderView(NULL, NULL);
    }

    psv = (void *)0xdeadbeef;
    hr = SHCreateShellFolderView(NULL, &psv);
    ok(hr == E_INVALIDARG, "Got 0x%08x\n", hr);
    ok(psv == NULL, "psv = %p\n", psv);

    memset(&sfvc, 0, sizeof(sfvc));
    psv = (void *)0xdeadbeef;
    hr = SHCreateShellFolderView(&sfvc, &psv);
    ok(hr == E_INVALIDARG, "Got 0x%08x\n", hr);
    ok(psv == NULL, "psv = %p\n", psv);

    memset(&sfvc, 0, sizeof(sfvc));
    sfvc.cbSize = sizeof(sfvc) - 1;
    psv = (void *)0xdeadbeef;
    hr = SHCreateShellFolderView(&sfvc, &psv);
    ok(hr == E_INVALIDARG, "Got 0x%08x\n", hr);
    ok(psv == NULL, "psv = %p\n", psv);

    memset(&sfvc, 0, sizeof(sfvc));
    sfvc.cbSize = sizeof(sfvc) + 1;
    psv = (void *)0xdeadbeef;
    hr = SHCreateShellFolderView(&sfvc, &psv);
    ok(hr == E_INVALIDARG, "Got 0x%08x\n", hr);
    ok(psv == NULL, "psv = %p\n", psv);

if (0)
{
    /* Crashes on NULL 'pshf' on XP/2k3 */
    memset(&sfvc, 0, sizeof(sfvc));
    sfvc.cbSize = sizeof(sfvc);
    psv = (void *)0xdeadbeef;
    hr = SHCreateShellFolderView(&sfvc, &psv);
    ok(hr == E_UNEXPECTED, "Got 0x%08x\n", hr);
    ok(psv == NULL, "psv = %p\n", psv);
}
    memset(&sfvc, 0, sizeof(sfvc));
    sfvc.cbSize = sizeof(sfvc) - 1;
    sfvc.pshf = desktop;
    psv = (void *)0xdeadbeef;
    hr = SHCreateShellFolderView(&sfvc, &psv);
    ok(hr == E_INVALIDARG, "Got 0x%08x\n", hr);
    ok(psv == NULL, "psv = %p\n", psv);

    memset(&sfvc, 0, sizeof(sfvc));
    sfvc.cbSize = sizeof(sfvc);
    sfvc.pshf = desktop;
    psv = NULL;
    hr = SHCreateShellFolderView(&sfvc, &psv);
    ok(hr == S_OK, "Got 0x%08x\n", hr);
    ok(psv != NULL, "psv = %p\n", psv);

    hr = IShellView_QueryInterface(psv, &IID_CDefView, (void **)&unk);
    ok(hr == S_OK, "got (0x%08x)\n", hr);
    ok(unk == (IUnknown *)psv, "got %p\n", unk);
    IUnknown_Release(unk);

    refCount = IShellView_Release(psv);
    ok(refCount == 0, "refCount = %u\n", refCount);

    IShellFolder_Release(desktop);
}