#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nclm ;
struct TYPE_10__ {int /*<<< orphan*/  lfWeight; } ;
struct TYPE_9__ {int /*<<< orphan*/  clrInfoText; int /*<<< orphan*/  clrInfoBk; } ;
struct TYPE_8__ {int cbSize; TYPE_6__ lfStatusFont; } ;
struct TYPE_7__ {void* hTitleFont; void* hFont; int /*<<< orphan*/  clrText; int /*<<< orphan*/  clrBk; } ;
typedef  TYPE_1__ TOOLTIPS_INFO ;
typedef  TYPE_2__ NONCLIENTMETRICSW ;

/* Variables and functions */
 void* CreateFontIndirectW (TYPE_6__*) ; 
 int /*<<< orphan*/  DeleteObject (void*) ; 
 int /*<<< orphan*/  FW_BOLD ; 
 int /*<<< orphan*/  SPI_GETNONCLIENTMETRICS ; 
 int /*<<< orphan*/  SystemParametersInfoW (int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_3__ comctl32_color ; 

__attribute__((used)) static void
TOOLTIPS_InitSystemSettings (TOOLTIPS_INFO *infoPtr)
{
    NONCLIENTMETRICSW nclm;

    infoPtr->clrBk   = comctl32_color.clrInfoBk;
    infoPtr->clrText = comctl32_color.clrInfoText;

    DeleteObject (infoPtr->hFont);
    nclm.cbSize = sizeof(nclm);
    SystemParametersInfoW (SPI_GETNONCLIENTMETRICS, sizeof(nclm), &nclm, 0);
    infoPtr->hFont = CreateFontIndirectW (&nclm.lfStatusFont);

    DeleteObject (infoPtr->hTitleFont);
    nclm.lfStatusFont.lfWeight = FW_BOLD;
    infoPtr->hTitleFont = CreateFontIndirectW (&nclm.lfStatusFont);
}