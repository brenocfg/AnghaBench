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
typedef  int /*<<< orphan*/  IProgressDialog ;
typedef  int /*<<< orphan*/  IOleWindow ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_ProgressDialog ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ E_POINTER ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  IID_IOleWindow ; 
 int /*<<< orphan*/  IID_IProgressDialog ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ IOleWindow_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IOleWindow_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IProgressDialog_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IProgressDialog_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  win_skip (char*,scalar_t__) ; 

__attribute__((used)) static void test_IProgressDialog_QueryInterface(void)
{
    IProgressDialog *dlg;
    IProgressDialog *dlg2;
    IOleWindow *olewindow;
    IUnknown *unk;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_ProgressDialog, NULL, CLSCTX_INPROC_SERVER, &IID_IProgressDialog, (void*)&dlg);
    if (FAILED(hr)) {
        win_skip("CoCreateInstance for IProgressDialog returned 0x%x\n", hr);
        return;
    }

    hr = IProgressDialog_QueryInterface(dlg, &IID_IUnknown, NULL);
    ok(hr == E_POINTER, "got 0x%x (expected E_POINTER)\n", hr);

    hr = IProgressDialog_QueryInterface(dlg, &IID_IUnknown, (void**)&unk);
    ok(hr == S_OK, "QueryInterface (IUnknown) returned 0x%x\n", hr);
    if (SUCCEEDED(hr)) {
        IUnknown_Release(unk);
    }

    hr = IProgressDialog_QueryInterface(dlg, &IID_IOleWindow, (void**)&olewindow);
    ok(hr == S_OK, "QueryInterface (IOleWindow) returned 0x%x\n", hr);
    if (SUCCEEDED(hr)) {
        hr = IOleWindow_QueryInterface(olewindow, &IID_IProgressDialog, (void**)&dlg2);
        ok(hr == S_OK, "QueryInterface (IProgressDialog) returned 0x%x\n", hr);
        if (SUCCEEDED(hr)) {
            IProgressDialog_Release(dlg2);
        }
        IOleWindow_Release(olewindow);
    }
    IProgressDialog_Release(dlg);
}