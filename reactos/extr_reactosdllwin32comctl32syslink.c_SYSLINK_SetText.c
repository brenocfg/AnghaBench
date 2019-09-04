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
struct TYPE_6__ {int /*<<< orphan*/  Self; } ;
typedef  TYPE_1__ SYSLINK_INFO ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__* LPCWSTR ;
typedef  int /*<<< orphan*/ * HDC ;

/* Variables and functions */
 scalar_t__ GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYSLINK_ClearDoc (TYPE_1__*) ; 
 scalar_t__ SYSLINK_ParseText (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  SYSLINK_Render (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT SYSLINK_SetText (SYSLINK_INFO *infoPtr, LPCWSTR Text)
{
    /* clear the document */
    SYSLINK_ClearDoc(infoPtr);

    if(Text == NULL || *Text == 0)
    {
        return TRUE;
    }

    /* let's parse the string and create a document */
    if(SYSLINK_ParseText(infoPtr, Text) > 0)
    {
        RECT rcClient;

        /* Render text position and word wrapping in memory */
        if (GetClientRect(infoPtr->Self, &rcClient))
        {
            HDC hdc = GetDC(infoPtr->Self);
            if (hdc != NULL)
            {
                SYSLINK_Render(infoPtr, hdc, &rcClient);
                ReleaseDC(infoPtr->Self, hdc);

                InvalidateRect(infoPtr->Self, NULL, TRUE);
            }
        }
    }
    
    return TRUE;
}