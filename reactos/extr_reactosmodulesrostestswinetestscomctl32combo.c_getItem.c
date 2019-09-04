#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int iItem; int cchTextMax; int /*<<< orphan*/  pszText; int /*<<< orphan*/  mask; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ COMBOBOXEXITEMA ;

/* Variables and functions */
 int /*<<< orphan*/  CBEIF_TEXT ; 
 int /*<<< orphan*/  CBEM_GETITEMA ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  textBuffer ; 

__attribute__((used)) static LONG getItem(HWND cbex, int idx, COMBOBOXEXITEMA *cbItem) {
    memset(cbItem, 0x00, sizeof(COMBOBOXEXITEMA));
    cbItem->mask = CBEIF_TEXT;
    cbItem->pszText      = textBuffer;
    cbItem->iItem        = idx;
    cbItem->cchTextMax   = 100;
    return SendMessageA(cbex, CBEM_GETITEMA, 0, (LPARAM)cbItem);
}