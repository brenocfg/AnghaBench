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
typedef  int WORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
#define  VK_CAPITAL 138 
#define  VK_CONTROL 137 
#define  VK_ESCAPE 136 
#define  VK_LWIN 135 
#define  VK_MENU 134 
#define  VK_NUMLOCK 133 
#define  VK_PAUSE 132 
#define  VK_RETURN 131 
#define  VK_RWIN 130 
#define  VK_SCROLL 129 
#define  VK_SHIFT 128 

__attribute__((used)) static BOOL
IsSystemKey(WORD VirtualKeyCode)
{
    switch (VirtualKeyCode)
    {
        /* From MSDN, "Virtual-Key Codes" */
        case VK_RETURN:
        case VK_SHIFT:
        case VK_CONTROL:
        case VK_MENU:
        case VK_PAUSE:
        case VK_CAPITAL:
        case VK_ESCAPE:
        case VK_LWIN:
        case VK_RWIN:
        case VK_NUMLOCK:
        case VK_SCROLL:
            return TRUE;
        default:
            return FALSE;
    }
}