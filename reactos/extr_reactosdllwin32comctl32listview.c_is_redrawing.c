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
struct TYPE_3__ {int /*<<< orphan*/  redraw; } ;
typedef  TYPE_1__ LISTVIEW_INFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */

__attribute__((used)) static inline BOOL is_redrawing(const LISTVIEW_INFO *infoPtr)
{
    return infoPtr->redraw;
}