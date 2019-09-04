#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ cx; int /*<<< orphan*/  cy; } ;
struct TYPE_13__ {scalar_t__ nButtonWidth; scalar_t__ cxMin; scalar_t__ cxMax; int /*<<< orphan*/  iTopMargin; int /*<<< orphan*/  nButtonHeight; } ;
typedef  TYPE_1__ TOOLBAR_INFO ;
typedef  TYPE_2__ SIZE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TOOLBAR_CalcStrings (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  TOOLBAR_DumpToolbar (TYPE_1__*,int) ; 
 scalar_t__ TOOLBAR_IsValidImageList (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOOLBAR_LayoutToolbar (TYPE_1__*) ; 
 TYPE_2__ TOOLBAR_MeasureButton (TYPE_1__*,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  default_top_margin (TYPE_1__*) ; 

__attribute__((used)) static void
TOOLBAR_CalcToolbar (TOOLBAR_INFO *infoPtr)
{
    SIZE  sizeString, sizeButton;
    BOOL validImageList = FALSE;

    TOOLBAR_CalcStrings (infoPtr, &sizeString);

    TOOLBAR_DumpToolbar (infoPtr, __LINE__);

    if (TOOLBAR_IsValidImageList(infoPtr, 0))
        validImageList = TRUE;
    sizeButton = TOOLBAR_MeasureButton(infoPtr, sizeString, TRUE, validImageList);
    infoPtr->nButtonWidth = sizeButton.cx;
    infoPtr->nButtonHeight = sizeButton.cy;
    infoPtr->iTopMargin = default_top_margin(infoPtr);

    if ( infoPtr->cxMin >= 0 && infoPtr->nButtonWidth < infoPtr->cxMin )
        infoPtr->nButtonWidth = infoPtr->cxMin;
    if ( infoPtr->cxMax > 0 && infoPtr->nButtonWidth > infoPtr->cxMax )
        infoPtr->nButtonWidth = infoPtr->cxMax;

    TOOLBAR_LayoutToolbar(infoPtr);
}