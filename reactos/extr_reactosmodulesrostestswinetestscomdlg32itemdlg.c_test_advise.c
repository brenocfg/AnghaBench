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
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  IFileDialog ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_FileOpenDialog ; 
 int /*<<< orphan*/  CLSID_FileSaveDialog ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IFileDialog_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IFileDialog ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_advise_helper (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_advise(void)
{
    IFileDialog *pfd;
    HRESULT hr;
    LONG ref;

    trace("Testing FileOpenDialog (advise)\n");
    hr = CoCreateInstance(&CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER,
                          &IID_IFileDialog, (void**)&pfd);
    ok(hr == S_OK, "got 0x%08x.\n", hr);
    test_advise_helper(pfd);
    ref = IFileDialog_Release(pfd);
    ok(!ref, "Got refcount %d, should have been released.\n", ref);

    trace("Testing FileSaveDialog (advise)\n");
    hr = CoCreateInstance(&CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER,
                          &IID_IFileDialog, (void**)&pfd);
    ok(hr == S_OK, "got 0x%08x.\n", hr);
    test_advise_helper(pfd);
    ref = IFileDialog_Release(pfd);
    ok(!ref, "Got refcount %d, should have been released.\n", ref);
}