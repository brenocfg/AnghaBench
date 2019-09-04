#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_8__ {int mask; int /*<<< orphan*/  pszText; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pszText; } ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  COMBOEX_INFO ;
typedef  TYPE_1__ COMBOBOXEXITEMW ;
typedef  TYPE_2__ COMBOBOXEXITEMA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * Alloc (int) ; 
 int CBEIF_TEXT ; 
 int /*<<< orphan*/  COMBOEX_SetItemW (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ is_textA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_2__ const*,int) ; 

__attribute__((used)) static BOOL COMBOEX_SetItemA (COMBOEX_INFO *infoPtr, COMBOBOXEXITEMA const *cit)
{
    COMBOBOXEXITEMW citW;
    LPWSTR wstr = NULL;
    BOOL ret;

    memcpy(&citW, cit, sizeof(COMBOBOXEXITEMA));
    if ((cit->mask & CBEIF_TEXT) && is_textA(cit->pszText)) {
	INT len = MultiByteToWideChar (CP_ACP, 0, cit->pszText, -1, NULL, 0);
        wstr = Alloc ((len + 1)*sizeof(WCHAR));
	if (!wstr) return FALSE;
	MultiByteToWideChar (CP_ACP, 0, cit->pszText, -1, wstr, len);
	citW.pszText = wstr;
    }
    ret = COMBOEX_SetItemW(infoPtr, &citW);

    Free(wstr);

    return ret;
}