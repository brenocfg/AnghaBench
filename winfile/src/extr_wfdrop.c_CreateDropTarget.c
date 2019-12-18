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
typedef  int /*<<< orphan*/  WF_IDropTarget ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * WF_IDropTarget_new (int /*<<< orphan*/ ) ; 

HRESULT CreateDropTarget(HWND hwnd, WF_IDropTarget **ppDropTarget) 
{
	if(ppDropTarget == 0)
		return E_INVALIDARG;

	*ppDropTarget = WF_IDropTarget_new(hwnd);

	return (*ppDropTarget) ? S_OK : E_OUTOFMEMORY;

}