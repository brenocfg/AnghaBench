#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_13__ {scalar_t__ y; int /*<<< orphan*/  x; } ;
struct TYPE_10__ {int dwFlags; } ;
struct TYPE_12__ {TYPE_1__ ppshheader; scalar_t__ hasHelp; } ;
struct TYPE_11__ {scalar_t__ top; scalar_t__ bottom; int /*<<< orphan*/  left; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__ PropSheetInfo ;
typedef  TYPE_4__ POINT ;
typedef  TYPE_5__ PADDING_INFO ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  IDCANCEL ; 
 int /*<<< orphan*/  IDC_NEXT_BUTTON ; 
 int /*<<< orphan*/  IDC_SUNKEN_LINE ; 
 int /*<<< orphan*/  IDHELP ; 
 int INTRNL_ANY_WIZARD ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  TRACE (char*) ; 

__attribute__((used)) static PADDING_INFO PROPSHEET_GetPaddingInfoWizard(HWND hwndDlg, const PropSheetInfo*
 psInfo)
{
  PADDING_INFO padding;
  RECT rc;
  HWND hwndControl;
  INT idButton;
  POINT ptButton, ptLine;

  TRACE("\n");
  if (psInfo->hasHelp)
  {
	idButton = IDHELP;
  }
  else
  {
    if (psInfo->ppshheader.dwFlags & INTRNL_ANY_WIZARD)
    {
	idButton = IDC_NEXT_BUTTON;
    }
    else
    {
	/* hopefully this is ok */
	idButton = IDCANCEL;
    }
  }

  hwndControl = GetDlgItem(hwndDlg, idButton);
  GetWindowRect(hwndControl, &rc);
  MapWindowPoints( 0, hwndDlg, (POINT *)&rc, 2 );
  ptButton.x = rc.left;
  ptButton.y = rc.top;

  /* Line */
  hwndControl = GetDlgItem(hwndDlg, IDC_SUNKEN_LINE);
  GetWindowRect(hwndControl, &rc);
  MapWindowPoints( 0, hwndDlg, (POINT *)&rc, 2 );
  ptLine.x = rc.left;
  ptLine.y = rc.bottom;

  padding.y = ptButton.y - ptLine.y;

  if (padding.y < 0)
	  ERR("padding negative ! Please report this !\n");

  /* this is most probably not correct, but the best we have now */
  padding.x = padding.y;
  return padding;
}