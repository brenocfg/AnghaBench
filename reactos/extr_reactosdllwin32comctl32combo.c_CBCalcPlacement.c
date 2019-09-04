#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ droppedWidth; } ;
struct TYPE_14__ {scalar_t__ bottom; scalar_t__ top; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_1__* LPRECT ;
typedef  TYPE_2__* LPHEADCOMBO ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 scalar_t__ CBGetTextAreaHeight (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ CBS_DROPDOWN ; 
 scalar_t__ CBS_DROPDOWNLIST ; 
 scalar_t__ CBS_SIMPLE ; 
 scalar_t__ CB_GETTYPE (TYPE_2__*) ; 
 scalar_t__ COMBO_EDITBUTTONSPACE () ; 
 int /*<<< orphan*/  COMBO_XBORDERSIZE () ; 
 int /*<<< orphan*/  COMBO_YBORDERSIZE () ; 
 int /*<<< orphan*/  CopyRect (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_CONTROL_PADDING () ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InflateRect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXVSCROLL ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_1__*) ; 

__attribute__((used)) static void CBCalcPlacement(
  HWND        hwnd,
  LPHEADCOMBO lphc,
  LPRECT      lprEdit,
  LPRECT      lprButton,
  LPRECT      lprLB)
{
  /*
   * Again, start with the client rectangle.
   */
  GetClientRect(hwnd, lprEdit);

  /*
   * Remove the borders
   */
  InflateRect(lprEdit, -COMBO_XBORDERSIZE(), -COMBO_YBORDERSIZE());

  /*
   * Chop off the bottom part to fit with the height of the text area.
   */
  lprEdit->bottom = lprEdit->top + CBGetTextAreaHeight(hwnd, lphc);

  /*
   * The button starts the same vertical position as the text area.
   */
  CopyRect(lprButton, lprEdit);

  /*
   * If the combobox is "simple" there is no button.
   */
  if( CB_GETTYPE(lphc) == CBS_SIMPLE )
    lprButton->left = lprButton->right = lprButton->bottom = 0;
  else
  {
    /*
     * Let's assume the combobox button is the same width as the
     * scrollbar button.
     * size the button horizontally and cut-off the text area.
     */
    lprButton->left = lprButton->right - GetSystemMetrics(SM_CXVSCROLL);
    lprEdit->right  = lprButton->left;
  }

  /*
   * In the case of a dropdown, there is an additional spacing between the
   * text area and the button.
   */
  if( CB_GETTYPE(lphc) == CBS_DROPDOWN )
  {
    lprEdit->right -= COMBO_EDITBUTTONSPACE();
  }

  /*
   * If we have an edit control, we space it away from the borders slightly.
   */
  if (CB_GETTYPE(lphc) != CBS_DROPDOWNLIST)
  {
    InflateRect(lprEdit, -EDIT_CONTROL_PADDING(), -EDIT_CONTROL_PADDING());
  }

  /*
   * Adjust the size of the listbox popup.
   */
  if( CB_GETTYPE(lphc) == CBS_SIMPLE )
  {
    /*
     * Use the client rectangle to initialize the listbox rectangle
     */
    GetClientRect(hwnd, lprLB);

    /*
     * Then, chop-off the top part.
     */
    lprLB->top = lprEdit->bottom + COMBO_YBORDERSIZE();
  }
  else
  {
    /*
     * Make sure the dropped width is as large as the combobox itself.
     */
    if (lphc->droppedWidth < (lprButton->right + COMBO_XBORDERSIZE()))
    {
      lprLB->right  = lprLB->left + (lprButton->right + COMBO_XBORDERSIZE());

      /*
       * In the case of a dropdown, the popup listbox is offset to the right.
       * so, we want to make sure it's flush with the right side of the
       * combobox
       */
      if( CB_GETTYPE(lphc) == CBS_DROPDOWN )
	lprLB->right -= COMBO_EDITBUTTONSPACE();
    }
    else
       lprLB->right = lprLB->left + lphc->droppedWidth;
  }

  /* don't allow negative window width */
  if (lprEdit->right < lprEdit->left)
    lprEdit->right = lprEdit->left;

  TRACE("\ttext\t= (%s)\n", wine_dbgstr_rect(lprEdit));

  TRACE("\tbutton\t= (%s)\n", wine_dbgstr_rect(lprButton));

  TRACE("\tlbox\t= (%s)\n", wine_dbgstr_rect(lprLB));
}