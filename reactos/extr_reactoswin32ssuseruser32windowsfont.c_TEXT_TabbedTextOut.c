#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int left; int top; int right; int bottom; } ;
struct TYPE_8__ {int cx; int cy; } ;
struct TYPE_7__ {int tmAveCharWidth; int tmHeight; } ;
typedef  TYPE_1__ TEXTMETRICW ;
typedef  TYPE_2__ SIZE ;
typedef  TYPE_3__ RECT ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ETO_OPAQUE ; 
 int /*<<< orphan*/  ExtTextOutW (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,TYPE_3__*,char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ GetBkMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextExtentPointW (int /*<<< orphan*/ ,char*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  GetTextMetricsW (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MAKELONG (int,int) ; 
 scalar_t__ OPAQUE ; 
 int abs (int const) ; 

LONG TEXT_TabbedTextOut( HDC hdc,
                         INT x,
                         INT y,
                         LPCWSTR lpstr,
                         INT count,
                         INT cTabStops,
                         const INT *lpTabPos,
                         INT nTabOrg,
                         BOOL fDisplayText )
{
    INT defWidth;
    SIZE extent;
    int i, j;
    int start = x;
    TEXTMETRICW tm;

    if (!lpTabPos)
        cTabStops=0;

    GetTextMetricsW( hdc, &tm );

    if (cTabStops == 1)
    {
        defWidth = *lpTabPos;
        cTabStops = 0;
    }
    else
    {
        defWidth = 8 * tm.tmAveCharWidth;
    }

    while (count > 0)
    {
        RECT r;
        INT x0;
        x0 = x;
        r.left = x0;
        /* chop the string into substrings of 0 or more <tabs>
         * possibly followed by 1 or more normal characters */
        for (i = 0; i < count; i++)
            if (lpstr[i] != '\t') break;
        for (j = i; j < count; j++)
            if (lpstr[j] == '\t') break;
        /* get the extent of the normal character part */
        GetTextExtentPointW( hdc, lpstr + i, j - i , &extent );
        /* and if there is a <tab>, calculate its position */
        if( i) {
            /* get x coordinate for the drawing of this string */
            for (; cTabStops > i; lpTabPos++, cTabStops--)
            {
                if( nTabOrg + abs( *lpTabPos) > x) {
                    if( lpTabPos[ i - 1] >= 0) {
                        /* a left aligned tab */
                        x = nTabOrg + lpTabPos[ i-1] + extent.cx;
                        break;
                    }
                    else
                    {
                        /* if tab pos is negative then text is right-aligned
                         * to tab stop meaning that the string extends to the
                         * left, so we must subtract the width of the string */
                        if (nTabOrg - lpTabPos[ i - 1] - extent.cx > x)
                        {
                            x = nTabOrg - lpTabPos[ i - 1];
                            x0 = x - extent.cx;
                            break;
                        }
                    }
                }
            }
            /* if we have run out of tab stops and we have a valid default tab
             * stop width then round x up to that width */
            if ((cTabStops <= i) && (defWidth > 0)) {
                x0 = nTabOrg + ((x - nTabOrg) / defWidth + i) * defWidth;
                x = x0 + extent.cx;
            } else if ((cTabStops <= i) && (defWidth < 0)) {
                x = nTabOrg + ((x - nTabOrg + extent.cx) / -defWidth + i)
                    * -defWidth;
                x0 = x - extent.cx;
            }
        } else
            x += extent.cx;

        if (fDisplayText)
        {
            r.top    = y;
            r.right  = x;
            r.bottom = y + extent.cy;

            ExtTextOutW( hdc, x0, y, GetBkMode(hdc) == OPAQUE ? ETO_OPAQUE : 0,
                         &r, lpstr + i, j - i, NULL );
        }
        count -= j;
        lpstr += j;
    }

    if(!extent.cy)
        extent.cy = tm.tmHeight;

    return MAKELONG(x - start, extent.cy);
}