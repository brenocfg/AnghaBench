#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cbexItem ;
struct TYPE_3__ {int iItem; char* pszText; scalar_t__ cchTextMax; int /*<<< orphan*/  mask; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ COMBOBOXEXITEMA ;

/* Variables and functions */
 int /*<<< orphan*/  CBEIF_TEXT ; 
 int /*<<< orphan*/  CBEM_SETITEMA ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 

__attribute__((used)) static LONG setItem(HWND cbex, int idx, const char *text) {
    COMBOBOXEXITEMA cbexItem;
    memset(&cbexItem, 0x00, sizeof(cbexItem));
    cbexItem.mask = CBEIF_TEXT;
    cbexItem.iItem = idx;
    cbexItem.pszText    = (char*)text;
    cbexItem.cchTextMax = 0;
    return SendMessageA(cbex, CBEM_SETITEMA, 0, (LPARAM)&cbexItem);
}