#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  updating; int /*<<< orphan*/  hwndSelf; TYPE_1__* lpcc; } ;
struct TYPE_4__ {int /*<<< orphan*/  rgbResult; } ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  TYPE_2__ CCPRIV ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int GetBValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetGValue (int /*<<< orphan*/ ) ; 
 int GetRValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_COLOR_EDIT_B ; 
 int /*<<< orphan*/  IDC_COLOR_EDIT_G ; 
 int /*<<< orphan*/  IDC_COLOR_EDIT_R ; 
 int /*<<< orphan*/  IDC_COLOR_GRAPH ; 
 scalar_t__ IsWindowVisible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDlgItemInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void CC_EditSetRGB( CCPRIV *infoPtr )
{
 if (IsWindowVisible( GetDlgItem(infoPtr->hwndSelf, IDC_COLOR_GRAPH) ))   /* if full size */
 {
   COLORREF cr = infoPtr->lpcc->rgbResult;
   int r = GetRValue(cr);
   int g = GetGValue(cr);
   int b = GetBValue(cr);

   infoPtr->updating = TRUE;
   SetDlgItemInt(infoPtr->hwndSelf, IDC_COLOR_EDIT_R, r, TRUE);
   SetDlgItemInt(infoPtr->hwndSelf, IDC_COLOR_EDIT_G, g, TRUE);
   SetDlgItemInt(infoPtr->hwndSelf, IDC_COLOR_EDIT_B, b, TRUE);
   infoPtr->updating = FALSE;
 }
}