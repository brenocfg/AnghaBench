#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int fsStyle; } ;
struct TYPE_5__ {int /*<<< orphan*/  dwExStyle; } ;
typedef  TYPE_1__ TOOLBAR_INFO ;
typedef  TYPE_2__ TBUTTON_INFO ;
typedef  int BOOL ;

/* Variables and functions */
 int BTNS_DROPDOWN ; 
 int BTNS_WHOLEDROPDOWN ; 
 scalar_t__ TOOLBAR_HasDropDownArrows (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline BOOL button_has_ddarrow(const TOOLBAR_INFO *infoPtr, const TBUTTON_INFO *btnPtr)
{
    return (TOOLBAR_HasDropDownArrows( infoPtr->dwExStyle ) && (btnPtr->fsStyle & BTNS_DROPDOWN)) ||
        (btnPtr->fsStyle & BTNS_WHOLEDROPDOWN);
}