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
struct TYPE_4__ {int mask; int /*<<< orphan*/  pszText; int /*<<< orphan*/  lParam; int /*<<< orphan*/  iIndent; int /*<<< orphan*/  iOverlay; int /*<<< orphan*/  iSelectedImage; int /*<<< orphan*/  iImage; int /*<<< orphan*/  cchTextMax; } ;
typedef  TYPE_1__ CBE_ITEMDATA ;

/* Variables and functions */
 int CBEIF_TEXT ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__ const*,int,...) ; 
 int /*<<< orphan*/  debugstr_txt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void COMBOEX_DumpItem (CBE_ITEMDATA const *item)
{
    TRACE("item %p - mask=%08x, pszText=%p, cchTM=%d, iImage=%d\n",
          item, item->mask, item->pszText, item->cchTextMax, item->iImage);
    TRACE("item %p - iSelectedImage=%d, iOverlay=%d, iIndent=%d, lParam=%08lx\n",
          item, item->iSelectedImage, item->iOverlay, item->iIndent, item->lParam);
    if (item->mask & CBEIF_TEXT)
        TRACE("item %p - pszText=%s\n", item, debugstr_txt(item->pszText));
}