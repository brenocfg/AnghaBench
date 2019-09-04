#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Self; int /*<<< orphan*/  Font; } ;
struct TYPE_5__ {scalar_t__ tmHeight; } ;
typedef  TYPE_1__ TEXTMETRICW ;
typedef  TYPE_2__ SYSLINK_INFO ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/  HGDIOBJ ;
typedef  int /*<<< orphan*/ * HDC ;

/* Variables and functions */
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 scalar_t__ GetTextMetricsW (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT SYSLINK_GetIdealHeight (const SYSLINK_INFO *infoPtr)
{
    HDC hdc = GetDC(infoPtr->Self);
    if(hdc != NULL)
    {
        LRESULT height;
        TEXTMETRICW tm;
        HGDIOBJ hOldFont = SelectObject(hdc, infoPtr->Font);
        
        if(GetTextMetricsW(hdc, &tm))
        {
            height = tm.tmHeight;
        }
        else
        {
            height = 0;
        }
        SelectObject(hdc, hOldFont);
        ReleaseDC(infoPtr->Self, hdc);
        
        return height;
    }
    return 0;
}