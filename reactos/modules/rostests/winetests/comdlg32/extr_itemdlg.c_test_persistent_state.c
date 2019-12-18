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
typedef  int /*<<< orphan*/  IFileDialog ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_FileOpenDialog ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IFileDialog_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IFileDialog_SetClientGuid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IFileDialog ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IID_NULL ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_persistent_state(void)
{
    IFileDialog *fd;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER,
                          &IID_IFileDialog, (void**)&fd);
    ok(hr == S_OK, "got 0x%08x.\n", hr);

if (0)
{
    /* crashes at least on Win8 */
    hr = IFileDialog_SetClientGuid(fd, NULL);
}

    hr = IFileDialog_SetClientGuid(fd, &IID_IUnknown);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IFileDialog_SetClientGuid(fd, &IID_NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    IFileDialog_Release(fd);
}