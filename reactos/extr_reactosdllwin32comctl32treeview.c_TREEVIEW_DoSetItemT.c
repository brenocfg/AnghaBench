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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
struct TYPE_6__ {int cchTextMax; scalar_t__ cChildren; scalar_t__ iImage; scalar_t__ iSelectedImage; scalar_t__ iExpandedImage; int state; int callbackMask; int /*<<< orphan*/  iIntegral; int /*<<< orphan*/  lParam; int /*<<< orphan*/ * pszText; scalar_t__ textWidth; } ;
struct TYPE_5__ {int mask; scalar_t__ cChildren; scalar_t__ iImage; scalar_t__ iSelectedImage; scalar_t__ iExpandedImage; int state; int stateMask; int /*<<< orphan*/  uStateEx; int /*<<< orphan*/  iIntegral; int /*<<< orphan*/  lParam; int /*<<< orphan*/ * pszText; } ;
typedef  TYPE_1__ TVITEMEXW ;
typedef  TYPE_2__ TREEVIEW_ITEM ;
typedef  int /*<<< orphan*/  TREEVIEW_INFO ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ I_CHILDRENCALLBACK ; 
 scalar_t__ I_IMAGECALLBACK ; 
 int /*<<< orphan*/ * LPSTR_TEXTCALLBACKW ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int TEXT_CALLBACK_SIZE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 
 int TVIF_CHILDREN ; 
 int TVIF_EXPANDEDIMAGE ; 
 int TVIF_IMAGE ; 
 int TVIF_INTEGRAL ; 
 int TVIF_PARAM ; 
 int TVIF_SELECTEDIMAGE ; 
 int TVIF_STATE ; 
 int TVIF_STATEEX ; 
 int TVIF_TEXT ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 void* heap_realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
TREEVIEW_DoSetItemT(const TREEVIEW_INFO *infoPtr, TREEVIEW_ITEM *item,
		   const TVITEMEXW *tvItem, BOOL isW)
{
    UINT callbackClear = 0;
    UINT callbackSet = 0;

    TRACE("item %p\n", item);
    /* Do this first in case it fails. */
    if (tvItem->mask & TVIF_TEXT)
    {
        item->textWidth = 0; /* force width recalculation */
	if (tvItem->pszText != LPSTR_TEXTCALLBACKW && tvItem->pszText != NULL) /* covers != TEXTCALLBACKA too, and undocumented: pszText of NULL also means TEXTCALLBACK */
	{
            int len;
            LPWSTR newText;
            if (isW)
                len = lstrlenW(tvItem->pszText) + 1;
            else
                len = MultiByteToWideChar(CP_ACP, 0, (LPSTR)tvItem->pszText, -1, NULL, 0);

            newText  = heap_realloc(item->pszText, len * sizeof(WCHAR));

            if (newText == NULL) return FALSE;

            callbackClear |= TVIF_TEXT;

            item->pszText = newText;
            item->cchTextMax = len;
            if (isW)
                lstrcpynW(item->pszText, tvItem->pszText, len);
            else
                MultiByteToWideChar(CP_ACP, 0, (LPSTR)tvItem->pszText, -1,
                                    item->pszText, len);

            TRACE("setting text %s, item %p\n", debugstr_w(item->pszText), item);
        }
	else
	{
            callbackSet |= TVIF_TEXT;
            item->pszText = heap_realloc(item->pszText, TEXT_CALLBACK_SIZE * sizeof(WCHAR));
	    item->cchTextMax = TEXT_CALLBACK_SIZE;
	    TRACE("setting callback, item %p\n", item);
	}
    }

    if (tvItem->mask & TVIF_CHILDREN)
    {
	item->cChildren = tvItem->cChildren;

	if (item->cChildren == I_CHILDRENCALLBACK)
	    callbackSet |= TVIF_CHILDREN;
	else
	    callbackClear |= TVIF_CHILDREN;
    }

    if (tvItem->mask & TVIF_IMAGE)
    {
	item->iImage = tvItem->iImage;

	if (item->iImage == I_IMAGECALLBACK)
	    callbackSet |= TVIF_IMAGE;
	else
	    callbackClear |= TVIF_IMAGE;
    }

    if (tvItem->mask & TVIF_SELECTEDIMAGE)
    {
	item->iSelectedImage = tvItem->iSelectedImage;

	if (item->iSelectedImage == I_IMAGECALLBACK)
	    callbackSet |= TVIF_SELECTEDIMAGE;
	else
	    callbackClear |= TVIF_SELECTEDIMAGE;
    }

    if (tvItem->mask & TVIF_EXPANDEDIMAGE)
    {
	item->iExpandedImage = tvItem->iExpandedImage;

	if (item->iExpandedImage == I_IMAGECALLBACK)
	    callbackSet |= TVIF_EXPANDEDIMAGE;
	else
	    callbackClear |= TVIF_EXPANDEDIMAGE;
    }

    if (tvItem->mask & TVIF_PARAM)
	item->lParam = tvItem->lParam;

    /* If the application sets TVIF_INTEGRAL without
     * supplying a TVITEMEX structure, it's toast. */
    if (tvItem->mask & TVIF_INTEGRAL)
	item->iIntegral = tvItem->iIntegral;

    if (tvItem->mask & TVIF_STATE)
    {
	TRACE("prevstate 0x%x, state 0x%x, mask 0x%x\n", item->state, tvItem->state,
	      tvItem->stateMask);
	item->state &= ~tvItem->stateMask;
	item->state |= (tvItem->state & tvItem->stateMask);
    }

    if (tvItem->mask & TVIF_STATEEX)
    {
        FIXME("New extended state: 0x%x\n", tvItem->uStateEx);
    }

    item->callbackMask |= callbackSet;
    item->callbackMask &= ~callbackClear;

    return TRUE;
}