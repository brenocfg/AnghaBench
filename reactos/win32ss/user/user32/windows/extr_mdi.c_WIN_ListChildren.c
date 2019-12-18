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
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtUserBuildHwndList (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 

HWND* WIN_ListChildren (HWND hWndparent)
{

  DWORD dwCount = 0;
  HWND* pHwnd = NULL;
  HANDLE hHeap;
  NTSTATUS Status;

  Status = NtUserBuildHwndList ( NULL, hWndparent, FALSE, 0, 0, NULL, &dwCount );

  if ( !NT_SUCCESS( Status ) )
    return 0;

  /* allocate buffer to receive HWND handles */
  hHeap = GetProcessHeap();

  pHwnd = HeapAlloc ( hHeap, 0, sizeof(HWND)*(dwCount+1) );
  if ( !pHwnd )
    {
      SetLastError ( ERROR_NOT_ENOUGH_MEMORY );
      return 0;
    }

  /* now call kernel again to fill the buffer this time */
  Status = NtUserBuildHwndList (NULL, hWndparent, FALSE, 0, 0, pHwnd, &dwCount );

  if ( !NT_SUCCESS( Status ) )
    {
      if ( pHwnd )
        HeapFree ( hHeap, 0, pHwnd );
      return 0;
    }

  pHwnd[dwCount] = (HWND) 0;

  return pHwnd;
}