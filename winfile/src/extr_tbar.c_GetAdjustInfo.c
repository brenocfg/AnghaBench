#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_12__ {scalar_t__ bUnicode; scalar_t__ Delta; scalar_t__ iStartBmp; int /*<<< orphan*/  (* ExtProc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  hMenu; } ;
struct TYPE_11__ {int idB; int idM; } ;
struct TYPE_10__ {int idCommand; void** szHelp; int /*<<< orphan*/  hMenu; } ;
struct TYPE_9__ {int iBitmap; int idCommand; int fsStyle; size_t dwData; int /*<<< orphan*/  fsState; } ;
struct TYPE_8__ {int iItem; void** pszText; TYPE_2__ tbButton; } ;
typedef  TYPE_1__* LPTBNOTIFY ;
typedef  TYPE_2__* LPTBBUTTON ;
typedef  scalar_t__ LPFMS_HELPSTRING ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  size_t INT ;
typedef  TYPE_3__ FMS_HELPSTRING ;
typedef  void* CHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTOF (void**) ; 
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FMEVENT_HELPSTRING ; 
 int HIDEIT ; 
 int /*<<< orphan*/  LoadDesc (int,void**) ; 
 int MAXDESCLEN ; 
 int /*<<< orphan*/  MB_PRECOMPOSED ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 scalar_t__ SendMessage (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrNCpy (void**,void**,int) ; 
 scalar_t__ TBAR_ALL_BUTTONS ; 
 int TBAR_BUTTON_COUNT ; 
 int /*<<< orphan*/  TBSTATE_ENABLED ; 
 int /*<<< orphan*/  TBSTATE_HIDDEN ; 
 int TBSTYLE_SEP ; 
 int /*<<< orphan*/  TB_GETBUTTON ; 
 void* TEXT (char) ; 
 scalar_t__ TRUE ; 
 TYPE_6__* extensions ; 
 scalar_t__ hwndExtensions ; 
 int /*<<< orphan*/  hwndFrame ; 
 scalar_t__ iNumExtensions ; 
 int /*<<< orphan*/  memcpy (void**,void**,int /*<<< orphan*/ ) ; 
 TYPE_5__* sAllButtons ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* tbButtons ; 

BOOL
GetAdjustInfo(LPTBNOTIFY lpTBNotify)
{
   LPTBBUTTON lpButton = &lpTBNotify->tbButton;
   FMS_HELPSTRING tbl;
   INT iExt;
   int j = lpTBNotify->iItem;


   if ((UINT)j < TBAR_ALL_BUTTONS) {

      *lpButton = tbButtons[TBAR_BUTTON_COUNT-1];
      lpButton->iBitmap = sAllButtons[j].idB & ~HIDEIT;
      lpButton->fsState = (sAllButtons[j].idB & HIDEIT)
         ? TBSTATE_HIDDEN : TBSTATE_ENABLED;
      lpButton->idCommand = sAllButtons[j].idM;

LoadDescription:
      lpTBNotify->pszText[0] = TEXT('\0');
      if (!(lpButton->fsStyle & TBSTYLE_SEP))
         LoadDesc(lpButton->idCommand, lpTBNotify->pszText);

UnlockAndReturn:
      return(TRUE);
   }

   j -= TBAR_ALL_BUTTONS;
   if (hwndExtensions && SendMessage(hwndExtensions, TB_GETBUTTON, j,
      (LPARAM)lpButton)) {

      if (lpButton->fsStyle & TBSTYLE_SEP)
         goto LoadDescription;

      iExt = lpButton->dwData - 1; // can now directly determine the extension with which the button is associated

      if ((UINT)iExt < (UINT)iNumExtensions) {
         tbl.idCommand = lpButton->idCommand % 100;
         tbl.hMenu = extensions[iExt].hMenu;
         tbl.szHelp[0] = TEXT('\0');

         extensions[iExt].ExtProc(hwndFrame, FMEVENT_HELPSTRING,
             (LPARAM)(LPFMS_HELPSTRING)&tbl);

         if (extensions[iExt].bUnicode == FALSE) {
            CHAR   szAnsi[MAXDESCLEN];

            memcpy (szAnsi, tbl.szHelp, COUNTOF(szAnsi));
            MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, szAnsi, COUNTOF(szAnsi),
                                 tbl.szHelp, COUNTOF(tbl.szHelp));
         }

         StrNCpy(lpTBNotify->pszText, tbl.szHelp, MAXDESCLEN - 1);

         // bias idCommand and iBitmap as if the button was in hwndToolbar
         lpButton->iBitmap += extensions[iExt].iStartBmp;
         lpButton->idCommand += extensions[iExt].Delta;

         goto UnlockAndReturn;
      }
   }

   return FALSE;
}