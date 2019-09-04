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
struct TYPE_6__ {int /*<<< orphan*/  lParam; int /*<<< orphan*/  iIndent; int /*<<< orphan*/  iOverlay; int /*<<< orphan*/  iSelectedImage; int /*<<< orphan*/  iImage; int /*<<< orphan*/  cchTextMax; scalar_t__* pszText; } ;
struct TYPE_5__ {int mask; int /*<<< orphan*/  lParam; int /*<<< orphan*/  iIndent; int /*<<< orphan*/  iOverlay; int /*<<< orphan*/  iSelectedImage; int /*<<< orphan*/  iImage; int /*<<< orphan*/  cchTextMax; scalar_t__* pszText; } ;
typedef  TYPE_1__ COMBOBOXEXITEMW ;
typedef  TYPE_2__ CBE_ITEMDATA ;

/* Variables and functions */
 int CBEIF_IMAGE ; 
 int CBEIF_INDENT ; 
 int CBEIF_LPARAM ; 
 int CBEIF_OVERLAY ; 
 int CBEIF_SELECTEDIMAGE ; 
 int CBEIF_TEXT ; 
 scalar_t__ is_textW (scalar_t__*) ; 
 int /*<<< orphan*/  lstrcpynW (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void COMBOEX_CopyItem (const CBE_ITEMDATA *item, COMBOBOXEXITEMW *cit)
{
    if (cit->mask & CBEIF_TEXT) {
        /*
         * when given a text buffer actually use that buffer
         */
        if (cit->pszText) {
	    if (is_textW(item->pszText))
                lstrcpynW(cit->pszText, item->pszText, cit->cchTextMax);
	    else
		cit->pszText[0] = 0;
        } else {
            cit->pszText        = item->pszText;
            cit->cchTextMax     = item->cchTextMax;
        }
    }
    if (cit->mask & CBEIF_IMAGE)
	cit->iImage         = item->iImage;
    if (cit->mask & CBEIF_SELECTEDIMAGE)
	cit->iSelectedImage = item->iSelectedImage;
    if (cit->mask & CBEIF_OVERLAY)
	cit->iOverlay       = item->iOverlay;
    if (cit->mask & CBEIF_INDENT)
	cit->iIndent        = item->iIndent;
    if (cit->mask & CBEIF_LPARAM)
	cit->lParam         = item->lParam;
}