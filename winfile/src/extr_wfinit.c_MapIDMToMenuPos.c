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
typedef  int UINT ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_STYLE ; 
 int GetWindowLongPtr (scalar_t__,int /*<<< orphan*/ ) ; 
 int IDM_EXTENSIONS ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  WM_MDIGETACTIVE ; 
 int WS_MAXIMIZE ; 
 scalar_t__ bSecMenuDeleted ; 
 int /*<<< orphan*/  hwndMDIClient ; 

UINT
MapIDMToMenuPos(UINT idm)
{
    UINT pos;

    if (idm < 100)
    {
        // idm values < 100 are just the top level menu IDM_ value (e.g., IDM_FILE)
        pos = idm;
    }
    else
    {
        // these are the built in or extension menu IDM_ values; IDM_OPEN is 101 and thus pos will be 0 (IDM_FILE)
        pos = idm / 100 - 1;
    }

    // if maximized, menu position shifted one to the right
    HWND hwndActive;
    hwndActive = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, 0L);
    if (hwndActive && GetWindowLongPtr(hwndActive, GWL_STYLE) & WS_MAXIMIZE)
        pos++;

    // if pos >= IDM_EXTENSIONS, subtract one if security menu missing
    if (pos >= IDM_EXTENSIONS && bSecMenuDeleted)
    {
        pos--;
    }

    return pos;
}