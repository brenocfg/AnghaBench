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
typedef  size_t INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t ARRAYSIZE (scalar_t__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDC_ZOOMM ; 
 int /*<<< orphan*/  IDC_ZOOMP ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_ZOOM ; 
 scalar_t__ MIN_ZOOM ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TB_ENABLEBUTTON ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ZoomPercents ; 
 scalar_t__* ZoomSteps ; 
 int /*<<< orphan*/  hDispWnd ; 
 int /*<<< orphan*/  hToolBar ; 

__attribute__((used)) static void ZoomInOrOut(BOOL bZoomIn)
{
    INT i;

    if (bZoomIn)    /* zoom in */
    {
        /* find next step */
        for (i = 0; i < ARRAYSIZE(ZoomSteps); ++i)
        {
            if (ZoomPercents < ZoomSteps[i])
                break;
        }
        if (i == ARRAYSIZE(ZoomSteps))
            ZoomPercents = MAX_ZOOM;
        else
            ZoomPercents = ZoomSteps[i];

        /* update tool bar buttons */
        SendMessage(hToolBar, TB_ENABLEBUTTON, IDC_ZOOMM, TRUE);
        if (ZoomPercents >= MAX_ZOOM)
            SendMessage(hToolBar, TB_ENABLEBUTTON, IDC_ZOOMP, FALSE);
        else
            SendMessage(hToolBar, TB_ENABLEBUTTON, IDC_ZOOMP, TRUE);
    }
    else            /* zoom out */
    {
        /* find previous step */
        for (i = ARRAYSIZE(ZoomSteps); i > 0; )
        {
            --i;
            if (ZoomSteps[i] < ZoomPercents)
                break;
        }
        if (i < 0)
            ZoomPercents = MIN_ZOOM;
        else
            ZoomPercents = ZoomSteps[i];

        /* update tool bar buttons */
        SendMessage(hToolBar, TB_ENABLEBUTTON, IDC_ZOOMP, TRUE);
        if (ZoomPercents <= MIN_ZOOM)
            SendMessage(hToolBar, TB_ENABLEBUTTON, IDC_ZOOMM, FALSE);
        else
            SendMessage(hToolBar, TB_ENABLEBUTTON, IDC_ZOOMM, TRUE);
    }

    /* redraw */
    InvalidateRect(hDispWnd, NULL, TRUE);
}