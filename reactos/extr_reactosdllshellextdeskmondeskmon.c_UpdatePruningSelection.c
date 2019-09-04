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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {int bPruningOn; int /*<<< orphan*/  hwndDlg; TYPE_1__* DeskExtInterface; int /*<<< orphan*/  bKeyIsReadOnly; scalar_t__ bModesPruned; } ;
struct TYPE_5__ {int /*<<< orphan*/  Context; int /*<<< orphan*/  (* SetPruningMode ) (int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_2__* PDESKMONITOR ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ BST_UNCHECKED ; 
 int /*<<< orphan*/  GetParent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_PRUNINGCHECK ; 
 scalar_t__ IsDlgButtonChecked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PropSheet_Changed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateRefreshFrequencyList (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static VOID
UpdatePruningSelection(PDESKMONITOR This)
{
    BOOL bPruningOn;

    if (This->DeskExtInterface != NULL && This->bModesPruned && !This->bKeyIsReadOnly)
    {
        bPruningOn = IsDlgButtonChecked(This->hwndDlg,
                                        IDC_PRUNINGCHECK) != BST_UNCHECKED;

        if (bPruningOn != This->bPruningOn)
        {
            /* Tell desk.cpl to turn on/off pruning mode */
            This->bPruningOn = bPruningOn;
            This->DeskExtInterface->SetPruningMode(This->DeskExtInterface->Context,
                                                   bPruningOn);

            /* Fill the refresh rate combobox again, we now receive a filtered
               or unfiltered device mode list from desk.cpl (depending on whether
               pruning is active or not) */
            UpdateRefreshFrequencyList(This);

            (void)PropSheet_Changed(GetParent(This->hwndDlg),
                                    This->hwndDlg);
        }
    }
}