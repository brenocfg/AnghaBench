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
typedef  int /*<<< orphan*/  WND_DATA ;
typedef  int /*<<< orphan*/ * PWND_DATA ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ GetPropW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ MAKEINTATOM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPropW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atWndContext ; 

PWND_DATA ThemeGetWndData(HWND hWnd)
{
    PWND_DATA pwndData;

    pwndData = (PWND_DATA)GetPropW(hWnd, (LPCWSTR)MAKEINTATOM(atWndContext));
    if(pwndData == NULL)
    {
        pwndData = HeapAlloc(GetProcessHeap(), 
                            HEAP_ZERO_MEMORY, 
                            sizeof(WND_DATA));
        if(pwndData == NULL)
        {
            return NULL;
        }
        
        SetPropW( hWnd, (LPCWSTR)MAKEINTATOM(atWndContext), pwndData);
    }

    return pwndData;
}