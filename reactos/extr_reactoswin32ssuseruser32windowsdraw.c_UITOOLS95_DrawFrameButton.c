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
typedef  int /*<<< orphan*/  LPRECT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  DFCS_BUTTON3STATE 133 
#define  DFCS_BUTTONCHECK 132 
#define  DFCS_BUTTONPUSH 131 
#define  DFCS_BUTTONRADIO 130 
#define  DFCS_BUTTONRADIOIMAGE 129 
#define  DFCS_BUTTONRADIOMASK 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UITOOLS95_DFC_ButtonCheckRadio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UITOOLS95_DFC_ButtonPush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL UITOOLS95_DrawFrameButton(HDC hdc, LPRECT rc, UINT uState)
{
    switch(uState & 0xff)
    {
        case DFCS_BUTTONPUSH:
            return UITOOLS95_DFC_ButtonPush(hdc, rc, uState);

        case DFCS_BUTTONCHECK:
        case DFCS_BUTTON3STATE:
            return UITOOLS95_DFC_ButtonCheckRadio(hdc, rc, uState, FALSE);

        case DFCS_BUTTONRADIOIMAGE:
        case DFCS_BUTTONRADIOMASK:
        case DFCS_BUTTONRADIO:
            return UITOOLS95_DFC_ButtonCheckRadio(hdc, rc, uState, TRUE);

/*
        default:
            DbgPrint("Invalid button state=0x%04x\n", uState);
*/
    }

    return FALSE;
}