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
struct TYPE_3__ {int /*<<< orphan*/  hwndTarget; } ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HICON ;
typedef  TYPE_1__ GHOST_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  GCLP_HICON ; 
 int /*<<< orphan*/  GCLP_HICONSM ; 
 int /*<<< orphan*/  GetClassLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* Ghost_GetData (int /*<<< orphan*/ ) ; 
#define  ICON_BIG 129 
#define  ICON_SMALL 128 

__attribute__((used)) static HICON
Ghost_GetIcon(HWND hwnd, INT fType)
{
    GHOST_DATA *pData = Ghost_GetData(hwnd);
    HICON hIcon = NULL;

    if (!pData)
        return NULL;

    // same as the original icon
    switch (fType)
    {
        case ICON_BIG:
        {
            hIcon = (HICON)GetClassLongPtrW(pData->hwndTarget, GCLP_HICON);
            break;
        }

        case ICON_SMALL:
        {
            hIcon = (HICON)GetClassLongPtrW(pData->hwndTarget, GCLP_HICONSM);
            break;
        }
    }

    return hIcon;
}