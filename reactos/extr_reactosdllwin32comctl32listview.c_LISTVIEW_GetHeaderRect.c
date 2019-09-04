#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  rcHeader; } ;
typedef  int /*<<< orphan*/ * LPRECT ;
typedef  int /*<<< orphan*/  LISTVIEW_INFO ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 TYPE_1__* LISTVIEW_GetColumnInfo (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void LISTVIEW_GetHeaderRect(const LISTVIEW_INFO *infoPtr, INT nSubItem, LPRECT lprc)
{
    *lprc = LISTVIEW_GetColumnInfo(infoPtr, nSubItem)->rcHeader;
}