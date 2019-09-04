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
struct TYPE_3__ {int dwStyle; int /*<<< orphan*/  date; int /*<<< orphan*/  hwndCheckbut; } ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ DATETIME_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  BM_GETCHECK ; 
 scalar_t__ BST_UNCHECKED ; 
 int DTS_SHOWNONE ; 
 int /*<<< orphan*/  GDT_NONE ; 
 int /*<<< orphan*/  GDT_VALID ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD
DATETIME_GetSystemTime (const DATETIME_INFO *infoPtr, SYSTEMTIME *systime)
{
    if (!systime) return GDT_NONE;

    if ((infoPtr->dwStyle & DTS_SHOWNONE) &&
        (SendMessageW (infoPtr->hwndCheckbut, BM_GETCHECK, 0, 0) == BST_UNCHECKED))
        return GDT_NONE;

    *systime = infoPtr->date;

    return GDT_VALID;
}