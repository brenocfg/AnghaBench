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
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_4__ {scalar_t__ hwndCheckbut; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ LPARAM ;
typedef  scalar_t__ HWND ;
typedef  TYPE_1__ DATETIME_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  DATETIME_Button_Command (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 

__attribute__((used)) static LRESULT
DATETIME_Command (DATETIME_INFO *infoPtr, WPARAM wParam, LPARAM lParam)
{
    TRACE("hwndbutton = %p\n", infoPtr->hwndCheckbut);
    if(infoPtr->hwndCheckbut == (HWND)lParam)
        return DATETIME_Button_Command(infoPtr, wParam, lParam);
    return 0;
}