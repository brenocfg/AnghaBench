#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int select; int* fieldspec; int nrFields; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  nCharsEntered; int /*<<< orphan*/  haveFocus; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int DWORD ;
typedef  TYPE_1__ DATETIME_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  DATETIME_IncreaseField (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  DATETIME_SendDateTimeChangeNotify (TYPE_1__*) ; 
 int /*<<< orphan*/  DATETIME_SetSelectedField (TYPE_1__*,int) ; 
 int DTHT_DATEFIELD ; 
 int DT_STRING ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int FORMATCALLMASK ; 
 int INT_MAX ; 
 int INT_MIN ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
#define  VK_ADD 135 
#define  VK_DOWN 134 
#define  VK_END 133 
#define  VK_HOME 132 
#define  VK_LEFT 131 
#define  VK_RIGHT 130 
#define  VK_SUBTRACT 129 
#define  VK_UP 128 

__attribute__((used)) static LRESULT
DATETIME_KeyDown (DATETIME_INFO *infoPtr, DWORD vkCode)
{
    int fieldNum = infoPtr->select & DTHT_DATEFIELD;
    int wrap = 0;
    int new;

    if (!(infoPtr->haveFocus)) return 0;
    if ((fieldNum==0) && (infoPtr->select)) return 0;

    if (infoPtr->select & FORMATCALLMASK) {
	FIXME ("Callbacks not implemented yet\n");
    }

    switch (vkCode) {
	case VK_ADD:
    	case VK_UP:
	    infoPtr->nCharsEntered = 0;
	    DATETIME_IncreaseField (infoPtr, fieldNum, 1);
	    DATETIME_SendDateTimeChangeNotify (infoPtr);
	    break;
	case VK_SUBTRACT:
	case VK_DOWN:
	    infoPtr->nCharsEntered = 0;
	    DATETIME_IncreaseField (infoPtr, fieldNum, -1);
	    DATETIME_SendDateTimeChangeNotify (infoPtr);
	    break;
	case VK_HOME:
	    infoPtr->nCharsEntered = 0;
	    DATETIME_IncreaseField (infoPtr, fieldNum, INT_MIN);
	    DATETIME_SendDateTimeChangeNotify (infoPtr);
	    break;
	case VK_END:
	    infoPtr->nCharsEntered = 0;
	    DATETIME_IncreaseField (infoPtr, fieldNum, INT_MAX);
	    DATETIME_SendDateTimeChangeNotify (infoPtr);
	    break;
	case VK_LEFT:
	    new = infoPtr->select;
	    do {
		if (new == 0) {
		    new = new - 1;
		    wrap++;
		} else {
		    new--;
		}
	    } while ((infoPtr->fieldspec[new] & DT_STRING) && (wrap<2));
	    if (new != infoPtr->select)
	        DATETIME_SetSelectedField(infoPtr, new);
	    break;
	case VK_RIGHT:
	    new = infoPtr->select;
	    do {
		new++;
		if (new==infoPtr->nrFields) {
		    new = 0;
		    wrap++;
		}
	    } while ((infoPtr->fieldspec[new] & DT_STRING) && (wrap<2));
	    if (new != infoPtr->select)
	        DATETIME_SetSelectedField(infoPtr, new);
	    break;
    }

    InvalidateRect(infoPtr->hwndSelf, NULL, TRUE);

    return 0;
}