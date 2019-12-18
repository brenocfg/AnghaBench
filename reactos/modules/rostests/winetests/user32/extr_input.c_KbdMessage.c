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
typedef  int WPARAM ;
typedef  int WORD ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  size_t KEV ;

/* Variables and functions */
 int* AsyncKeyStateTable ; 
 int* GETFLAGS ; 
 int /*<<< orphan*/ * GETSCAN ; 
 int* GETVKEY ; 
 int* InputKeyStateTable ; 
 int KEYEVENTF_EXTENDEDKEY ; 
 int KEYEVENTF_KEYUP ; 
 int KF_ALTDOWN ; 
 int KF_EXTENDED ; 
 int KF_REPEAT ; 
 int KF_UP ; 
 int LOBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELPARAM (int,int) ; 
 size_t TrackSysKey ; 
 int VK_CONTROL ; 
 size_t VK_MENU ; 
 int WM_KEYDOWN ; 
 int WM_KEYUP ; 
 int WM_SYSKEYDOWN ; 
 int WM_SYSKEYUP ; 

__attribute__((used)) static int KbdMessage( KEV kev, WPARAM *pwParam, LPARAM *plParam )
{
    UINT message;
    int VKey = GETVKEY[kev];
    WORD flags;

    flags = LOBYTE(GETSCAN[kev]);
    if (GETFLAGS[kev] & KEYEVENTF_EXTENDEDKEY) flags |= KF_EXTENDED;

    if (GETFLAGS[kev] & KEYEVENTF_KEYUP )
    {
        message = WM_KEYUP;
        if( (InputKeyStateTable[VK_MENU] & 0x80) && (
                (VKey == VK_MENU) || (VKey == VK_CONTROL) ||
                 !(InputKeyStateTable[VK_CONTROL] & 0x80))) {
            if(  TrackSysKey == VK_MENU || /* <ALT>-down/<ALT>-up sequence */
                    (VKey != VK_MENU)) /* <ALT>-down...<something else>-up */
                message = WM_SYSKEYUP;
            TrackSysKey = 0;
        }
        InputKeyStateTable[VKey] &= ~0x80;
        flags |= KF_REPEAT | KF_UP;
    }
    else
    {
        if (InputKeyStateTable[VKey] & 0x80) flags |= KF_REPEAT;
        if (!(InputKeyStateTable[VKey] & 0x80)) InputKeyStateTable[VKey] ^= 0x01;
        InputKeyStateTable[VKey] |= 0x80;
        AsyncKeyStateTable[VKey] |= 0x80;

        message = WM_KEYDOWN;
        if( (InputKeyStateTable[VK_MENU] & 0x80) &&
                !(InputKeyStateTable[VK_CONTROL] & 0x80)) {
            message = WM_SYSKEYDOWN;
            TrackSysKey = VKey;
        }
    }

    if (InputKeyStateTable[VK_MENU] & 0x80) flags |= KF_ALTDOWN;

    if( plParam) *plParam = MAKELPARAM( 1, flags );
    if( pwParam) *pwParam = VKey;
    return message;
}