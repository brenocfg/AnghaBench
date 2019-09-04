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
struct TYPE_3__ {int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_1__ NATIVEFONT_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
 TYPE_1__* Alloc (int) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT
NATIVEFONT_Create (HWND hwnd)
{
    NATIVEFONT_INFO *infoPtr;

    /* allocate memory for info structure */
    infoPtr = Alloc (sizeof(NATIVEFONT_INFO));
    SetWindowLongPtrW (hwnd, 0, (DWORD_PTR)infoPtr);

    /* initialize info structure */
    infoPtr->hwndSelf = hwnd;

    return 0;
}