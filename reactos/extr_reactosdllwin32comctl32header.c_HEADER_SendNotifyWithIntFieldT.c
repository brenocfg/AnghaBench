#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {size_t cxy; size_t iOrder; size_t mask; int /*<<< orphan*/  iImage; int /*<<< orphan*/  lParam; int /*<<< orphan*/  fmt; scalar_t__ cchTextMax; int /*<<< orphan*/ * pszText; int /*<<< orphan*/  hbm; } ;
struct TYPE_8__ {TYPE_1__* items; } ;
struct TYPE_7__ {size_t cxy; size_t iOrder; int /*<<< orphan*/  iImage; int /*<<< orphan*/  lParam; int /*<<< orphan*/  fmt; int /*<<< orphan*/  hbm; } ;
typedef  size_t INT ;
typedef  TYPE_2__ HEADER_INFO ;
typedef  TYPE_3__ HDITEMW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,size_t) ; 
#define  HDI_ORDER 129 
#define  HDI_WIDTH 128 
 int /*<<< orphan*/  HEADER_SendNotifyWithHDItemT (TYPE_2__ const*,int /*<<< orphan*/ ,size_t,TYPE_3__*) ; 

__attribute__((used)) static BOOL
HEADER_SendNotifyWithIntFieldT(const HEADER_INFO *infoPtr, UINT code, INT iItem, INT mask, INT iValue)
{
    HDITEMW nmitem;

    /* copying only the iValue should be ok but to make the code more robust we copy everything */
    nmitem.cxy = infoPtr->items[iItem].cxy;
    nmitem.hbm = infoPtr->items[iItem].hbm;
    nmitem.pszText = NULL;
    nmitem.cchTextMax = 0;
    nmitem.fmt = infoPtr->items[iItem].fmt;
    nmitem.lParam = infoPtr->items[iItem].lParam;
    nmitem.iOrder = infoPtr->items[iItem].iOrder;
    nmitem.iImage = infoPtr->items[iItem].iImage;

    nmitem.mask = mask;
    switch (mask)
    {
	case HDI_WIDTH:
	    nmitem.cxy = iValue;
	    break;
	case HDI_ORDER:
	    nmitem.iOrder = iValue;
	    break;
	default:
	    ERR("invalid mask value 0x%x\n", iValue);
    }

    return HEADER_SendNotifyWithHDItemT(infoPtr, code, iItem, &nmitem);
}