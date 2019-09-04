#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* items; } ;
struct TYPE_4__ {int /*<<< orphan*/  iOrder; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  size_t INT ;
typedef  TYPE_1__ HEADER_ITEM ;
typedef  TYPE_2__ HEADER_INFO ;

/* Variables and functions */

__attribute__((used)) static inline LRESULT
HEADER_IndexToOrder (const HEADER_INFO *infoPtr, INT iItem)
{
    HEADER_ITEM *lpItem = &infoPtr->items[iItem];
    return lpItem->iOrder;
}