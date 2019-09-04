#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hwndCombo; int /*<<< orphan*/  himl; } ;
typedef  int /*<<< orphan*/  HIMAGELIST ;
typedef  TYPE_1__ COMBOEX_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  COMBOEX_AdjustEditPos (TYPE_1__*) ; 
 int /*<<< orphan*/  COMBOEX_ReSize (TYPE_1__*) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static HIMAGELIST COMBOEX_SetImageList (COMBOEX_INFO *infoPtr, HIMAGELIST himl)
{
    HIMAGELIST himlTemp = infoPtr->himl;

    TRACE("\n");

    infoPtr->himl = himl;

    COMBOEX_ReSize (infoPtr);
    InvalidateRect (infoPtr->hwndCombo, NULL, TRUE);

    /* reposition the Edit control based on whether icon exists */
    COMBOEX_AdjustEditPos (infoPtr);
    return himlTemp;
}