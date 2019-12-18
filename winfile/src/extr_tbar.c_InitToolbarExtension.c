#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tbl ;
typedef  size_t WORD ;
typedef  void* UINT_PTR ;
struct TYPE_10__ {size_t iStartBmp; scalar_t__ idBitmap; int /*<<< orphan*/ * hbmButtons; scalar_t__ hModule; int /*<<< orphan*/  (* ExtProc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int dwSize; size_t cButtons; TYPE_3__* lpButtons; scalar_t__ idBitmap; int /*<<< orphan*/ * hBitmap; } ;
struct TYPE_8__ {int fsStyle; scalar_t__ idCommand; } ;
struct TYPE_7__ {void* nID; scalar_t__ hInst; } ;
struct TYPE_6__ {size_t iBitmap; int fsStyle; size_t dwData; scalar_t__ iString; scalar_t__ fsState; scalar_t__ idCommand; } ;
typedef  TYPE_1__ TBBUTTON ;
typedef  TYPE_2__ TBADDBITMAP ;
typedef  scalar_t__ LPTBBUTTON ;
typedef  scalar_t__ LPFMS_TOOLBARLOAD ;
typedef  TYPE_3__* LPEXT_BUTTON ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  size_t INT ;
typedef  TYPE_4__ FMS_TOOLBARLOAD ;
typedef  int BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CreateToolbarEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FMEVENT_TOOLBARLOAD ; 
 int /*<<< orphan*/  IDB_TOOLBAR ; 
 int /*<<< orphan*/  IDC_EXTENSIONS ; 
 int /*<<< orphan*/  LastButtonIsSeparator (scalar_t__) ; 
 scalar_t__ SendMessage (scalar_t__,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ TBSTATE_ENABLED ; 
 int TBSTYLE_SEP ; 
 int /*<<< orphan*/  TB_ADDBITMAP ; 
 int /*<<< orphan*/  TB_INSERTBUTTON ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WS_CHILD ; 
 TYPE_5__* extensions ; 
 int /*<<< orphan*/  hAppInstance ; 
 scalar_t__ hwndExtensions ; 
 int /*<<< orphan*/  hwndFrame ; 
 scalar_t__ hwndToolbar ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tbButtons ; 

BOOL
InitToolbarExtension(INT iExt)
{
   TBBUTTON extButton;
   FMS_TOOLBARLOAD tbl;
   LPEXT_BUTTON lpButton;
   INT i, iStart, iBitmap;
   BOOL fSepLast;
   TBADDBITMAP tbAddBitmap;

   tbl.dwSize = sizeof(tbl);
   tbl.lpButtons = NULL;
   tbl.cButtons = 0;
   tbl.idBitmap = 0;
   tbl.hBitmap = NULL;


   if (!extensions[iExt].ExtProc(hwndFrame, FMEVENT_TOOLBARLOAD,
       (LPARAM)(LPFMS_TOOLBARLOAD)&tbl))

      return FALSE;

   if (tbl.dwSize != sizeof(tbl)) {

      if (!(0x10 == tbl.dwSize && tbl.idBitmap))

         return FALSE;
   }

   if (!tbl.cButtons || !tbl.lpButtons || (!tbl.idBitmap && !tbl.hBitmap))
      return FALSE;

   // We add all extension buttons to a "dummy" toolbar

   if (hwndExtensions) {
      // If the last "button" is not a separator, then add one.  If it is, and
      // there are no extensions yet, then "include" it in the extensions.

      if (!LastButtonIsSeparator(hwndExtensions))
         goto AddSep;
   } else {
      hwndExtensions = CreateToolbarEx(hwndFrame, WS_CHILD,
         IDC_EXTENSIONS, 0, hAppInstance, IDB_TOOLBAR, tbButtons, 0,
         0,0,0,0,sizeof(TBBUTTON));

      if (!hwndExtensions)
         return FALSE;

AddSep:
      extButton.iBitmap = 0;
      extButton.idCommand = 0;
      extButton.fsState = 0;
      extButton.fsStyle = TBSTYLE_SEP;
      extButton.dwData = 0;
      extButton.iString = 0;

      SendMessage(hwndExtensions, TB_INSERTBUTTON, (WORD)-1,
         (LPARAM)(LPTBBUTTON)&extButton);
   }

   // Notice we add the bitmaps to hwndToolbar, not hwndExtensions, because
   // it is hwndToolbar that may actually paint the buttons.

   if (tbl.idBitmap) {
      tbAddBitmap.hInst = extensions[iExt].hModule;
      tbAddBitmap.nID   = (UINT_PTR)tbl.idBitmap;
      iStart = (INT)SendMessage(hwndToolbar, TB_ADDBITMAP, tbl.cButtons,
                               (LPARAM) &tbAddBitmap);
   } else {
      tbAddBitmap.hInst = 0;
      tbAddBitmap.nID   = (UINT_PTR)tbl.hBitmap;
      iStart = (INT)SendMessage(hwndToolbar, TB_ADDBITMAP, tbl.cButtons,
                               (LPARAM) &tbAddBitmap);
   }

   // fill in toolbar image information
   extensions[iExt].hbmButtons = tbl.hBitmap;
   extensions[iExt].idBitmap = tbl.idBitmap;
   extensions[iExt].iStartBmp = iStart;

   // Add all of his buttons.  Non-separator items have bitmap images in sequence.
   // idCommand and iBitmap values in hwndExtensions are the unbiased ones;
   // when saving toolbar customization, we save the unbiased idCommand and iBitmap.

   for (fSepLast=TRUE, i=tbl.cButtons, iBitmap=0, lpButton=tbl.lpButtons;
      i>0; --i, ++lpButton) {

      if (lpButton->fsStyle & TBSTYLE_SEP) {
         if (fSepLast)
            continue;

         extButton.iBitmap = 0;
         fSepLast = TRUE;
      } else {
         extButton.iBitmap = iBitmap;       // will be biased with iStart when added to hwndToolbar
         ++iBitmap;
         fSepLast = FALSE;
      }

      extButton.fsStyle   = (BYTE)lpButton->fsStyle;
      extButton.idCommand = lpButton->idCommand;    // will be biased with Delta when added to hwndToolbar
      extButton.fsState   = TBSTATE_ENABLED;
      extButton.dwData    = iExt + 1;     // 1 based iExt for command and bitmap start mapping
      extButton.iString   = 0;

      SendMessage(hwndExtensions, TB_INSERTBUTTON, (WORD)-1,
         (LPARAM)(LPTBBUTTON)&extButton);
   }

   return TRUE;
}