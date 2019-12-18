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
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/ * LPRECT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BF_ADJUST ; 
 int BF_MIDDLE ; 
 int BF_MONO ; 
 int BF_RECT ; 
 int BF_SOFT ; 
 int /*<<< orphan*/  COLOR_BTNFACE ; 
 int DFCS_ADJUSTRECT ; 
 int DFCS_CHECKED ; 
 int DFCS_FLAT ; 
 int DFCS_MONO ; 
 int DFCS_PUSHED ; 
 int EDGE_RAISED ; 
 int EDGE_SUNKEN ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSysColorBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InflateRect (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  IntDrawRectEdge (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UITOOLS_DrawCheckedRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL UITOOLS95_DFC_ButtonPush(HDC dc, LPRECT r, UINT uFlags)
{
    UINT edge;
    RECT myr = *r;

    if(uFlags & (DFCS_PUSHED | DFCS_CHECKED | DFCS_FLAT))
        edge = EDGE_SUNKEN;
    else
        edge = EDGE_RAISED;

    if(uFlags & DFCS_CHECKED)
    {
        if(uFlags & DFCS_MONO)
            IntDrawRectEdge(dc, &myr, edge, BF_MONO|BF_RECT|BF_ADJUST, 1);
        else
            IntDrawRectEdge(dc, &myr, edge, (uFlags&DFCS_FLAT)|BF_RECT|BF_SOFT|BF_ADJUST, 1);

        UITOOLS_DrawCheckedRect( dc, &myr );
    }
    else
    {
        if(uFlags & DFCS_MONO)
        {
            IntDrawRectEdge(dc, &myr, edge, BF_MONO|BF_RECT|BF_ADJUST, 1);
            FillRect(dc, &myr, GetSysColorBrush(COLOR_BTNFACE));
        }
        else
        {
            IntDrawRectEdge(dc, r, edge, (uFlags&DFCS_FLAT) | BF_MIDDLE | BF_RECT | BF_SOFT, 1);
        }
    }

    /* Adjust rectangle if asked */
    if(uFlags & DFCS_ADJUSTRECT)
        InflateRect(r, -2, -2);

    return TRUE;
}