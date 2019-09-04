#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  LISTVIEW_INFO ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  LISTVIEW_GetItemBox (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LISTVIEW_InvalidateRect (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_redrawing (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline void LISTVIEW_InvalidateItem(const LISTVIEW_INFO *infoPtr, INT nItem)
{
    RECT rcBox;

    if(!is_redrawing(infoPtr)) return; 
    LISTVIEW_GetItemBox(infoPtr, nItem, &rcBox);
    LISTVIEW_InvalidateRect(infoPtr, &rcBox);
}