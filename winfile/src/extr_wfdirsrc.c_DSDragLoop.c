#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WPARAM ;
typedef  scalar_t__ WORD ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {scalar_t__ hwndSink; scalar_t__ dwControlData; int /*<<< orphan*/  ptDrop; } ;
struct TYPE_5__ {int dwAttrs; } ;
typedef  TYPE_1__* LPXDTA ;
typedef  scalar_t__ LPTSTR ;
typedef  TYPE_2__* LPDROPSTRUCT ;
typedef  long LPARAM ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ HWND ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int ATTR_DIR ; 
 int FALSE ; 
 int /*<<< orphan*/  FS_GETDRIVE ; 
 scalar_t__ GetDrive (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetKeyState (int /*<<< orphan*/ ) ; 
 scalar_t__ GetMDIChildFromDescendant (scalar_t__) ; 
 int /*<<< orphan*/  GetMoveCopyCursor () ; 
 scalar_t__ GetParent (scalar_t__) ; 
 scalar_t__ HasDirWindow (scalar_t__) ; 
 scalar_t__ IsProgramFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 int /*<<< orphan*/  LoadCursor (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ MAKEINTRESOURCE (int) ; 
 int /*<<< orphan*/  MemGetFileName (TYPE_1__*) ; 
 scalar_t__ SendMessage (scalar_t__,int /*<<< orphan*/ ,scalar_t__,long) ; 
 int /*<<< orphan*/  SetCursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowItemBitmaps (scalar_t__,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  VK_CONTROL ; 
 int /*<<< orphan*/  VK_MENU ; 
 int /*<<< orphan*/  VK_SHIFT ; 
 int /*<<< orphan*/  hAppInstance ; 
 scalar_t__ hwndGlobalSink ; 
 int iCurDrag ; 

VOID
DSDragLoop(HWND hwndLB, WPARAM wParam, LPDROPSTRUCT lpds)
{
   BOOL bShowBitmap;
   LPXDTA lpxdta;
   HWND hwndMDIChildSink, hwndDir;
   BOOL bForceMoveCur = FALSE;

   //
   // bShowBitmap is used to turn the source bitmaps on or off to distinguish
   // between a move and a copy or to indicate that a drop can
   // occur (exec and app)
   //
   // hack: keep around for drop files!
   //
   hwndGlobalSink = lpds->hwndSink;

   //
   // default to copy
   //
   bShowBitmap = TRUE;

   //
   // can't drop here
   //
   if (!wParam)
      goto DragLoopCont;

   //
   // Is the user holding down the CTRL key (which forces a copy)?
   //
   if (GetKeyState(VK_CONTROL) < 0) {
       bShowBitmap = TRUE;
       goto DragLoopCont;
   }

   //
   // Is the user holding down the ALT or SHIFT key (which forces a move)?
   //
   if (GetKeyState(VK_MENU)<0 || GetKeyState(VK_SHIFT)<0) {
      bShowBitmap = FALSE;
      goto DragLoopCont;
   }

   hwndMDIChildSink = GetMDIChildFromDescendant(lpds->hwndSink);

   //
   // Are we over the source listbox? (sink and source the same)
   //
   if (lpds->hwndSink == hwndLB) {

      //
      // Are we over a valid listbox entry?
      //
      if (lpds->dwControlData == (DWORD)-1) {

         //
         // Now force move cursor
         //
         bForceMoveCur = TRUE;
         goto DragLoopCont;

      } else {

         //
         // are we over a directory entry?
         //
         SendMessage(hwndLB, LB_GETTEXT, (WPARAM)(lpds->dwControlData), (LPARAM)&lpxdta);

         if (!(lpxdta && lpxdta->dwAttrs & ATTR_DIR)) {

            //
            // Now force move cursor
            //
            bForceMoveCur = TRUE;

            goto DragLoopCont;
         }
      }
   }

   //
   // Now we need to see if we are over an Executable file.  If so, we
   // need to force the Bitmaps to draw.
   //

   //
   // Are we over a directory window?
   //
   if (hwndMDIChildSink)
      hwndDir = HasDirWindow(hwndMDIChildSink);
   else
      hwndDir = NULL;

   if (hwndDir && (hwndDir == GetParent(lpds->hwndSink))) {

      //
      // Are we over an occupied part of the list box?
      //
      if (lpds->dwControlData != (DWORD)-1) {

         //
         // Are we over an Executable?
         //
         SendMessage(lpds->hwndSink, LB_GETTEXT, (WORD)(lpds->dwControlData), (LPARAM)(LPTSTR)&lpxdta);

         if (lpxdta && IsProgramFile(MemGetFileName(lpxdta))) {
            goto DragLoopCont;
         }
      }
   }

   //
   // Are we dropping into the same drive (check the source and dest drives)
   //
   bShowBitmap = ((INT)SendMessage(GetParent(hwndLB), FS_GETDRIVE, 0, 0L) !=
                  GetDrive(lpds->hwndSink, lpds->ptDrop));

DragLoopCont:

   ShowItemBitmaps(hwndLB, bShowBitmap);

   //
   // hack, set the cursor to match the move/copy state
   //
   if (wParam) {
      if (bForceMoveCur) {
         SetCursor(LoadCursor(hAppInstance, (LPTSTR) MAKEINTRESOURCE(iCurDrag & ~1)));
      } else {
         SetCursor(GetMoveCopyCursor());
      }
   }
}