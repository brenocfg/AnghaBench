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
struct TYPE_4__ {int /*<<< orphan*/  uVItemPadding_s; int /*<<< orphan*/  uHItemPadding_s; } ;
typedef  TYPE_1__ TAB_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;

/* Variables and functions */
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline LRESULT
TAB_SetPadding (TAB_INFO *infoPtr, LPARAM lParam)
{
    TRACE("(%p %d %d)\n", infoPtr, LOWORD(lParam), HIWORD(lParam));
    infoPtr->uHItemPadding_s = LOWORD(lParam);
    infoPtr->uVItemPadding_s = HIWORD(lParam);

    return 0;
}