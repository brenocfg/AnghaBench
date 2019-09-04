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
typedef  int UINT ;
struct TYPE_4__ {int ref; } ;
typedef  TYPE_1__ IFileDialogEventsImpl ;
typedef  int /*<<< orphan*/  IFileDialogEvents ;
typedef  int /*<<< orphan*/  IFileDialog ;
typedef  int HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int E_INVALIDARG ; 
 int /*<<< orphan*/ * IFileDialogEvents_Constructor () ; 
 int /*<<< orphan*/  IFileDialogEvents_Release (int /*<<< orphan*/ *) ; 
 int IFileDialog_Advise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int IFileDialog_Unadvise (int /*<<< orphan*/ *,int) ; 
 int S_OK ; 
 int /*<<< orphan*/  ensure_zero_events (TYPE_1__*) ; 
 TYPE_1__* impl_from_IFileDialogEvents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_advise_helper(IFileDialog *pfd)
{
    IFileDialogEventsImpl *pfdeimpl;
    IFileDialogEvents *pfde;
    DWORD cookie[10];
    UINT i;
    HRESULT hr;

    pfde = IFileDialogEvents_Constructor();
    pfdeimpl = impl_from_IFileDialogEvents(pfde);

    /* Null pointer tests crash on Windows 10 16299 or newer */
    if (0)
    {
        hr = IFileDialog_Advise(pfd, NULL, NULL);
        ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);
        hr = IFileDialog_Advise(pfd, pfde, NULL);
        ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);
    }
    hr = IFileDialog_Advise(pfd, NULL, &cookie[0]);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);
    ok(pfdeimpl->ref == 1, "got ref %d\n", pfdeimpl->ref);
    ensure_zero_events(pfdeimpl);

    hr = IFileDialog_Unadvise(pfd, 0);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);
    for(i = 0; i < 10; i++) {
        hr = IFileDialog_Advise(pfd, pfde, &cookie[i]);
        ok(hr == S_OK, "got 0x%08x\n", hr);
        ok(cookie[i] == i+cookie[0], "Got cookie: %d\n", cookie[i]);
    }
    ok(pfdeimpl->ref == 10+1, "got ref %d\n", pfdeimpl->ref);
    ensure_zero_events(pfdeimpl);

    for(i = 3; i < 7; i++) {
        hr = IFileDialog_Unadvise(pfd, cookie[i]);
        ok(hr == S_OK, "got 0x%08x\n", hr);
    }
    ok(pfdeimpl->ref == 6+1, "got ref %d\n", pfdeimpl->ref);
    ensure_zero_events(pfdeimpl);

    for(i = 0; i < 3; i++) {
        hr = IFileDialog_Unadvise(pfd, cookie[i]);
        ok(hr == S_OK, "got 0x%08x\n", hr);
    }
    ok(pfdeimpl->ref == 3+1, "got ref %d\n", pfdeimpl->ref);
    ensure_zero_events(pfdeimpl);

    for(i = 7; i < 10; i++) {
        hr = IFileDialog_Unadvise(pfd, cookie[i]);
        ok(hr == S_OK, "got 0x%08x\n", hr);
    }
    ok(pfdeimpl->ref == 1, "got ref %d\n", pfdeimpl->ref);
    ensure_zero_events(pfdeimpl);

    hr = IFileDialog_Unadvise(pfd, cookie[9]+1);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);
    ok(pfdeimpl->ref == 1, "got ref %d\n", pfdeimpl->ref);
    ensure_zero_events(pfdeimpl);

    hr = IFileDialog_Advise(pfd, pfde, &cookie[0]);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(cookie[0] >= 1, "got cookie: %d\n", cookie[0]);
    ok(pfdeimpl->ref == 1+1, "got ref %d\n", pfdeimpl->ref);
    ensure_zero_events(pfdeimpl);

    hr = IFileDialog_Unadvise(pfd, cookie[0]);

    if(0)
    {
        /* Unadvising already unadvised cookies crashes on
           Windows 7. */
        IFileDialog_Unadvise(pfd, cookie[0]);
    }


    IFileDialogEvents_Release(pfde);
}