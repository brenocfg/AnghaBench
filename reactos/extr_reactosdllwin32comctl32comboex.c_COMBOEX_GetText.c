#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nmce ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_11__ {int /*<<< orphan*/ * pszText; int /*<<< orphan*/ * pszTemp; int /*<<< orphan*/  lParam; } ;
struct TYPE_9__ {int mask; int /*<<< orphan*/ * pszText; int /*<<< orphan*/  iItem; int /*<<< orphan*/  lParam; } ;
struct TYPE_10__ {TYPE_1__ ceItem; } ;
typedef  TYPE_2__ NMCOMBOBOXEXW ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  COMBOEX_INFO ;
typedef  TYPE_3__ CBE_ITEMDATA ;

/* Variables and functions */
 int /*<<< orphan*/ * Alloc (int) ; 
 int CBEIF_DI_SETITEM ; 
 int CBEIF_TEXT ; 
 int /*<<< orphan*/  CBEN_GETDISPINFOW ; 
 int /*<<< orphan*/  COMBOEX_FreeText (TYPE_3__*) ; 
 int /*<<< orphan*/  COMBOEX_GetIndex (int /*<<< orphan*/  const*,TYPE_3__*) ; 
 int /*<<< orphan*/  COMBOEX_NotifyItem (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LPSTR_TEXTCALLBACKW ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 scalar_t__ is_textW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static LPCWSTR COMBOEX_GetText(const COMBOEX_INFO *infoPtr, CBE_ITEMDATA *item)
{
    NMCOMBOBOXEXW nmce;
    LPWSTR text, buf;
    INT len;

    if (item->pszText != LPSTR_TEXTCALLBACKW)
	return item->pszText;

    ZeroMemory(&nmce, sizeof(nmce));
    nmce.ceItem.mask = CBEIF_TEXT;
    nmce.ceItem.lParam = item->lParam;
    nmce.ceItem.iItem = COMBOEX_GetIndex(infoPtr, item);
    COMBOEX_NotifyItem(infoPtr, CBEN_GETDISPINFOW, &nmce);

    if (is_textW(nmce.ceItem.pszText)) {
	len = MultiByteToWideChar (CP_ACP, 0, (LPSTR)nmce.ceItem.pszText, -1, NULL, 0);
        buf = Alloc ((len + 1)*sizeof(WCHAR));
	if (buf)
	    MultiByteToWideChar (CP_ACP, 0, (LPSTR)nmce.ceItem.pszText, -1, buf, len);
	if (nmce.ceItem.mask & CBEIF_DI_SETITEM) {
	    COMBOEX_FreeText(item);
	    item->pszText = buf;
	} else {
	    Free(item->pszTemp);
	    item->pszTemp = buf;
	}
	text = buf;
    } else
	text = nmce.ceItem.pszText;

    if (nmce.ceItem.mask & CBEIF_DI_SETITEM)
	item->pszText = text;
    return text;
}