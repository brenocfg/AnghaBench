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
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_ALL ; 
 int /*<<< orphan*/  CLSID_TaskbarList ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_ITaskbarList3 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * ptbl ; 
 int /*<<< orphan*/  uprintf (char*,int /*<<< orphan*/ ) ; 

BOOL CreateTaskbarList(void)
{
	HRESULT hr;

	hr = CoCreateInstance(&CLSID_TaskbarList, NULL, CLSCTX_ALL, &IID_ITaskbarList3, (LPVOID)&ptbl);
	if (FAILED(hr)) {
		uprintf("CoCreateInstance for TaskbarList failed: error %X\n", hr);
		ptbl = NULL;
		return FALSE;
	}
	return TRUE;
}