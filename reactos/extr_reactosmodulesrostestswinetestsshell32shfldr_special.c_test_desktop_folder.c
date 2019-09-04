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
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_POINTER ; 
 int /*<<< orphan*/  IID_IShellFolder ; 
 scalar_t__ IShellFolder_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SHGetDesktopFolder (int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_desktop_folder(void)
{
    IShellFolder *psf;
    HRESULT hr;

    hr = SHGetDesktopFolder(&psf);
    ok(hr == S_OK, "Got %x\n", hr);

    hr = IShellFolder_QueryInterface(psf, &IID_IShellFolder, NULL);
    ok(hr == E_POINTER, "Got %x\n", hr);

    IShellFolder_Release(psf);
}