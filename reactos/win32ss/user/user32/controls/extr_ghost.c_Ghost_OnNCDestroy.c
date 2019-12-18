#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ bDestroyTarget; int /*<<< orphan*/  hwndTarget; int /*<<< orphan*/ * hbm32bpp; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ GHOST_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FNID_DESTROY ; 
 int /*<<< orphan*/  GHOST_PROP ; 
 int /*<<< orphan*/  GWLP_USERDATA ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  Ghost_DestroyTarget (TYPE_1__*) ; 
 TYPE_1__* Ghost_GetData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  NtUserSetWindowFNID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostQuitMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemovePropW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW_SHOWNOACTIVATE ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindowAsync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
Ghost_OnNCDestroy(HWND hwnd)
{
    // delete the user data
    GHOST_DATA *pData = Ghost_GetData(hwnd);
    if (pData)
    {
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, 0);

        // delete image
        DeleteObject(pData->hbm32bpp);
        pData->hbm32bpp = NULL;

        // remove prop
        RemovePropW(pData->hwndTarget, GHOST_PROP);

        // show target
        ShowWindowAsync(pData->hwndTarget, SW_SHOWNOACTIVATE);

        // destroy target if necessary
        if (pData->bDestroyTarget)
        {
            Ghost_DestroyTarget(pData);
        }

        HeapFree(GetProcessHeap(), 0, pData);
    }

    NtUserSetWindowFNID(hwnd, FNID_DESTROY);

    PostQuitMessage(0);
}