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
typedef  int /*<<< orphan*/  LISTVIEW_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  LISTVIEW_InvalidateRect (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void LISTVIEW_InvalidateList(const LISTVIEW_INFO *infoPtr)
{
    LISTVIEW_InvalidateRect(infoPtr, NULL);
}