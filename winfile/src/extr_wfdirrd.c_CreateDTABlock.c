#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ wParam; } ;
typedef  TYPE_1__ MSG ;
typedef  int /*<<< orphan*/ * LPXDTALINK ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DirReadAbort (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIRABORT_NULL ; 
 int /*<<< orphan*/  EDIRABORT_READREQUEST ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  GWL_IERROR ; 
 int /*<<< orphan*/  MemDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PM_NOREMOVE ; 
 scalar_t__ PeekMessage (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * StealDTABlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VK_DOWN ; 
 scalar_t__ VK_UP ; 
 int /*<<< orphan*/  WM_KEYDOWN ; 

LPXDTALINK
CreateDTABlock(
   HWND hwnd,
   LPWSTR pPath,
   DWORD dwAttribs,
   BOOL bDontSteal)
{
   LPXDTALINK lpStart;
   MSG msg;

   SetWindowLongPtr(hwnd, GWL_IERROR, ERROR_SUCCESS);

   if (!bDontSteal && (lpStart = StealDTABlock(hwnd, pPath, dwAttribs))) {

      if (PeekMessage(&msg,
                      NULL,
                      WM_KEYDOWN,
                      WM_KEYDOWN,
                      PM_NOREMOVE)) {

         if (msg.wParam == VK_UP || msg.wParam == VK_DOWN) {

            MemDelete(lpStart);
            goto Abort;
         }
      }

      //
      // Abort the dir read, since we have stolen the correct thing.
      // (bAbort must be true to abort us, but the following call sets
      // lpStart to non-null, which prevents re-reading).
      //
      DirReadAbort(hwnd, lpStart, EDIRABORT_NULL);

      return lpStart;
   }

Abort:

   DirReadAbort(hwnd, NULL, EDIRABORT_READREQUEST);
   return NULL;
}