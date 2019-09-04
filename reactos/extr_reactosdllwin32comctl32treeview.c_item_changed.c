#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ cChildren; scalar_t__ iImage; scalar_t__ iSelectedImage; scalar_t__ iExpandedImage; scalar_t__ pszText; scalar_t__ iIntegral; int state; } ;
struct TYPE_6__ {int mask; int stateMask; } ;
typedef  TYPE_1__ TVITEMEXW ;
typedef  TYPE_2__ TREEVIEW_ITEM ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ I_IMAGECALLBACK ; 
 scalar_t__ LPSTR_TEXTCALLBACKW ; 
 int /*<<< orphan*/  TRUE ; 
 int TVIF_CHILDREN ; 
 int TVIF_EXPANDEDIMAGE ; 
 int TVIF_IMAGE ; 
 int TVIF_INTEGRAL ; 
 int TVIF_SELECTEDIMAGE ; 
 int TVIF_STATE ; 
 int TVIF_TEXT ; 

__attribute__((used)) static inline BOOL item_changed (const TREEVIEW_ITEM *tiOld, const TREEVIEW_ITEM *tiNew,
                                 const TVITEMEXW *tvChange)
{
    /* Number of children has changed */
    if ((tvChange->mask & TVIF_CHILDREN) && (tiOld->cChildren != tiNew->cChildren))
	return TRUE;

    /* Image has changed and it's not a callback */
    if ((tvChange->mask & TVIF_IMAGE) && (tiOld->iImage != tiNew->iImage) &&
	tiNew->iImage != I_IMAGECALLBACK)
	return TRUE;

    /* Selected image has changed and it's not a callback */
    if ((tvChange->mask & TVIF_SELECTEDIMAGE) && (tiOld->iSelectedImage != tiNew->iSelectedImage) &&
	tiNew->iSelectedImage != I_IMAGECALLBACK)
	return TRUE;

    if ((tvChange->mask & TVIF_EXPANDEDIMAGE) && (tiOld->iExpandedImage != tiNew->iExpandedImage) &&
	tiNew->iExpandedImage != I_IMAGECALLBACK)
	return TRUE;

    /* Text has changed and it's not a callback */
    if ((tvChange->mask & TVIF_TEXT) && (tiOld->pszText != tiNew->pszText) &&
	tiNew->pszText != LPSTR_TEXTCALLBACKW)
	return TRUE;

    /* Indent has changed */
    if ((tvChange->mask & TVIF_INTEGRAL) && (tiOld->iIntegral != tiNew->iIntegral))
	return TRUE;

    /* Item state has changed */
    if ((tvChange->mask & TVIF_STATE) && ((tiOld->state ^ tiNew->state) & tvChange->stateMask ))
	return TRUE;

    return FALSE;
}