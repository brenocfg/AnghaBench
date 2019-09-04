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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CreateICW (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 scalar_t__ InterlockedCompareExchangePointer (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  display_dc ; 

HDC get_display_dc(void)
{
    static const WCHAR displayW[] = {'D','I','S','P','L','A','Y',0};

    if(!display_dc) {
        HDC hdc;

        hdc = CreateICW(displayW, NULL, NULL, NULL);
        if(InterlockedCompareExchangePointer((void**)&display_dc, hdc, NULL))
            DeleteObject(hdc);
    }

    return display_dc;
}