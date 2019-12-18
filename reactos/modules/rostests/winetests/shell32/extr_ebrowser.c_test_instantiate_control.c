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
typedef  int /*<<< orphan*/  IExplorerBrowser ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IExplorerBrowser_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ REGDB_E_CLASSNOTREG ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ebrowser_instantiate (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static BOOL test_instantiate_control(void)
{
    IExplorerBrowser *peb;
    HRESULT hr;

    hr = ebrowser_instantiate(&peb);
    ok(hr == S_OK || hr == REGDB_E_CLASSNOTREG, "Got (0x%08x)\n", hr);
    if(FAILED(hr))
        return FALSE;

    IExplorerBrowser_Release(peb);
    return TRUE;
}