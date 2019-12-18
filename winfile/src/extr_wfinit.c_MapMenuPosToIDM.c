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
typedef  scalar_t__ UINT ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_STYLE ; 
 int GetWindowLongPtr (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ IDM_EXTENSIONS ; 
 scalar_t__ IDM_SECURITY ; 
 scalar_t__ MAX_EXTENSIONS ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  WM_MDIGETACTIVE ; 
 int WS_MAXIMIZE ; 
 scalar_t__ bSecMenuDeleted ; 
 int /*<<< orphan*/  hwndMDIClient ; 
 scalar_t__ iNumExtensions ; 

UINT  MapMenuPosToIDM(UINT pos)
{
    UINT idm = pos;

    // if maximized, idm is one position to the left
    HWND hwndActive;
    hwndActive = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, 0L);
    if (hwndActive && GetWindowLongPtr(hwndActive, GWL_STYLE) & WS_MAXIMIZE)
        idm--;

    // if pos >= IDM_SECURITY, add one if security menu missing
    if (idm >= IDM_SECURITY && bSecMenuDeleted)
    {
        idm++;
    }

    if (idm >= IDM_EXTENSIONS + iNumExtensions)
    {
        idm += MAX_EXTENSIONS - iNumExtensions;
    }

    return idm;
}