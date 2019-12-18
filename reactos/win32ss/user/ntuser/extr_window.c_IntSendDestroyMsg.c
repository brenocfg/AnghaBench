#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_3__* ppi; TYPE_13__* rpdesk; TYPE_14__* MessageQueue; } ;
struct TYPE_20__ {int style; int /*<<< orphan*/ * spwndParent; } ;
struct TYPE_19__ {TYPE_2__* prpwinsta; } ;
struct TYPE_18__ {TYPE_4__* spwndClipOwner; } ;
struct TYPE_17__ {scalar_t__ hWnd; } ;
struct TYPE_16__ {TYPE_1__ CaretInfo; TYPE_4__* spwndFocus; TYPE_4__* spwndActive; } ;
struct TYPE_15__ {TYPE_4__* spwndTrack; } ;
typedef  TYPE_4__* PWND ;
typedef  TYPE_5__* PTHREADINFO ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ExFreePoolWithTag (scalar_t__*,int /*<<< orphan*/ ) ; 
 TYPE_14__* IntGetFocusMessageQueue () ; 
 scalar_t__ IntIsWindow (scalar_t__) ; 
 int /*<<< orphan*/  IntRemoveTrackMouseEvent (TYPE_13__*) ; 
 scalar_t__* IntWinListChildren (TYPE_4__*) ; 
 TYPE_5__* PsGetCurrentThreadWin32Thread () ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  USERTAG_WINDOWLIST ; 
 int /*<<< orphan*/  UserClipboardRelease (TYPE_4__*) ; 
 TYPE_4__* UserGetWindowObject (scalar_t__) ; 
 scalar_t__ UserHMGetHandle (TYPE_4__*) ; 
 int /*<<< orphan*/  WM_DESTROY ; 
 int WS_CHILD ; 
 int WS_POPUP ; 
 int /*<<< orphan*/  co_IntDestroyCaret (TYPE_5__*) ; 
 int /*<<< orphan*/  co_IntSendMessage (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  co_UserSetFocus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  co_WinPosActivateOtherWindow (TYPE_4__*) ; 

__attribute__((used)) static void IntSendDestroyMsg(HWND hWnd)
{
   PTHREADINFO ti;
   PWND Window;

   ti = PsGetCurrentThreadWin32Thread();
   Window = UserGetWindowObject(hWnd);

   if (Window)
   {
      /*
       * Look whether the focus is within the tree of windows
       * we will be destroying.
       */
      // Rule #1
      if ( ti->MessageQueue->spwndActive == Window || // Fixes CORE-106 RegSvr32 exit and return focus to CMD.
          (ti->MessageQueue->spwndActive == NULL && ti->MessageQueue == IntGetFocusMessageQueue()) )
      {
         co_WinPosActivateOtherWindow(Window);
      }

      /* Fixes CMD properties closing and returning focus to CMD */
      if (ti->MessageQueue->spwndFocus == Window)
      {
         if ((Window->style & (WS_CHILD | WS_POPUP)) == WS_CHILD)
         {
            co_UserSetFocus(Window->spwndParent);
         }
         else
         {
            co_UserSetFocus(NULL);
         }
      }

      if (ti->MessageQueue->CaretInfo.hWnd == UserHMGetHandle(Window))
      {
         co_IntDestroyCaret(ti);
      }

      /* If the window being destroyed is currently tracked... */
      if (ti->rpdesk->spwndTrack == Window)
      {
          IntRemoveTrackMouseEvent(ti->rpdesk);
      }
   }

   /* If the window being destroyed is the current clipboard owner... */
   if (ti->ppi->prpwinsta != NULL && Window == ti->ppi->prpwinsta->spwndClipOwner)
   {
       /* ... make it release the clipboard */
       UserClipboardRelease(Window);
   }

   /* Send the WM_DESTROY to the window */
   co_IntSendMessage(hWnd, WM_DESTROY, 0, 0);

   /*
    * This WM_DESTROY message can trigger re-entrant calls to DestroyWindow
    * make sure that the window still exists when we come back.
    */
   if (IntIsWindow(hWnd))
   {
      HWND* pWndArray;
      int i;

      if (!(pWndArray = IntWinListChildren( Window ))) return;

      for (i = 0; pWndArray[i]; i++)
      {
         if (IntIsWindow( pWndArray[i] )) IntSendDestroyMsg( pWndArray[i] );
      }
      ExFreePoolWithTag(pWndArray, USERTAG_WINDOWLIST);
   }
   else
   {
      TRACE("destroyed itself while in WM_DESTROY!\n");
   }
}