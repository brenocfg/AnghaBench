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
struct TYPE_6__ {int cbSize; int /*<<< orphan*/  hwndList; int /*<<< orphan*/  hwndItem; int /*<<< orphan*/  hwndCombo; int /*<<< orphan*/  stateButton; int /*<<< orphan*/  rcButton; int /*<<< orphan*/  rcItem; } ;
struct TYPE_5__ {int wState; int /*<<< orphan*/  hWndLBox; int /*<<< orphan*/  hWndEdit; int /*<<< orphan*/  self; int /*<<< orphan*/  buttonRect; int /*<<< orphan*/  textRect; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ HEADCOMBO ;
typedef  TYPE_2__ COMBOBOXINFO ;

/* Variables and functions */
 int CBF_BUTTONDOWN ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IsRectEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATE_SYSTEM_INVISIBLE ; 
 int /*<<< orphan*/  STATE_SYSTEM_PRESSED ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT COMBO_GetComboBoxInfo(const HEADCOMBO *lphc, COMBOBOXINFO *pcbi)
{
    if (!pcbi || (pcbi->cbSize < sizeof(COMBOBOXINFO)))
        return FALSE;

    pcbi->rcItem = lphc->textRect;
    pcbi->rcButton = lphc->buttonRect;
    pcbi->stateButton = 0;
    if (lphc->wState & CBF_BUTTONDOWN)
        pcbi->stateButton |= STATE_SYSTEM_PRESSED;
    if (IsRectEmpty(&lphc->buttonRect))
        pcbi->stateButton |= STATE_SYSTEM_INVISIBLE;
    pcbi->hwndCombo = lphc->self;
    pcbi->hwndItem = lphc->hWndEdit;
    pcbi->hwndList = lphc->hWndLBox;
    return TRUE;
}