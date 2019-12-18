#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG_PTR ;
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int elpPenStyle; int elpWidth; int elpHatch; int elpNumEntries; scalar_t__ elpColor; scalar_t__ elpBrushStyle; } ;
typedef  TYPE_1__* PEXTLOGPEN ;
typedef  scalar_t__* PDWORD ;
typedef  int /*<<< orphan*/ * PBOOL ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ BS_DIBPATTERN ; 
 scalar_t__ BS_DIBPATTERNPT ; 
 scalar_t__ BS_HATCHED ; 
 scalar_t__ BS_NULL ; 
 scalar_t__ BS_PATTERN ; 
 scalar_t__ BS_SOLID ; 
 int /*<<< orphan*/  FALSE ; 
 int HS_API_MAX ; 
 int PS_ALTERNATE ; 
 int PS_COSMETIC ; 
 int PS_ENDCAP_MASK ; 
 int PS_INSIDEFRAME ; 
 int PS_JOIN_MASK ; 
 int PS_NULL ; 
 int PS_SOLID ; 
 int PS_STYLE_MASK ; 
 int PS_TYPE_MASK ; 
 int PS_USERSTYLE ; 
 scalar_t__ RGB (int,int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int abs (int /*<<< orphan*/ ) ; 

BOOL
Test_ExtCreatePen_Expect(
    DWORD dwPenStyle,
    DWORD dwWidth,
    DWORD dwStyleCount,
    PDWORD pdwStyles,
    UINT lbStyle,
    ULONG_PTR lbHatch,
    PBOOL pbExpectException,
    PEXTLOGPEN pelpExpect)
{
    *pbExpectException = FALSE;

    if ((dwPenStyle & PS_STYLE_MASK) == PS_USERSTYLE)
    {
        if (pdwStyles == NULL)
        {
            return FALSE;
        }
    }
    else
    {
        if ((dwStyleCount != 0) || (pdwStyles != NULL))
        {
            return FALSE;
        }
    }

    if (lbStyle == BS_PATTERN)
    {
        if (lbHatch == 0) return FALSE;
    }

    if (lbStyle == BS_DIBPATTERNPT)
    {
        if (lbHatch == 0) return FALSE;
        if (lbHatch < 0xFFFF)
        {
            *pbExpectException = TRUE;
            return FALSE;
        }
    }

    if (lbStyle == BS_DIBPATTERN)
    {
        return FALSE;
    }

    if ((dwPenStyle & PS_STYLE_MASK) == PS_USERSTYLE)
    {
        if (dwStyleCount == 0)
        {
            return FALSE;
        }

        if (dwStyleCount > 16)
        {
            return FALSE;
        }

        if ((dwPenStyle & PS_TYPE_MASK) == PS_COSMETIC)
        {
            if (pdwStyles[0] == 0)
            {
                return FALSE;
            }
        }
        else
        {
            if ((pdwStyles[0] == 0) && (dwStyleCount == 1))
            {
                return FALSE;
            }
        }
    }

    if ((dwPenStyle & PS_STYLE_MASK) == PS_NULL)
    {
        pelpExpect->elpPenStyle = PS_NULL;
        pelpExpect->elpWidth = 0;
        pelpExpect->elpBrushStyle = BS_SOLID;
        pelpExpect->elpColor = 0;
        pelpExpect->elpHatch = 0;
        pelpExpect->elpNumEntries = 0;
        return TRUE;
    }


    if (((dwPenStyle & PS_STYLE_MASK) >> 0) > PS_ALTERNATE) return FALSE;
    if (((dwPenStyle & PS_ENDCAP_MASK) >> 8) > 2) return FALSE;
    if (((dwPenStyle & PS_JOIN_MASK) >> 12) > 2) return FALSE;
    if (((dwPenStyle & PS_TYPE_MASK) >> 16) > 1) return FALSE;

    dwWidth = abs(((LONG)dwWidth));

    if ((dwPenStyle & PS_TYPE_MASK) == PS_COSMETIC)
    {
        if (dwWidth != 1) return FALSE;

        if ((lbStyle != BS_SOLID) &&
            (lbStyle != BS_HATCHED))
        {
            return FALSE;
        }

        if (lbStyle == BS_HATCHED)
        {
            if ((lbHatch != 8) &&
                (lbHatch != 10) &&
                (lbHatch != 12))
            {
                return FALSE;
            }

            if (lbHatch >= HS_API_MAX)
            {
                return FALSE;
            }
        }

        if ((dwPenStyle & PS_STYLE_MASK) == PS_INSIDEFRAME)
        {
            return FALSE;
        }
    }
    else
    {
        if ((dwPenStyle & PS_STYLE_MASK) == PS_ALTERNATE)
        {
            return FALSE;
        }

        if (((dwPenStyle & PS_STYLE_MASK) != PS_SOLID) &&
            ((dwPenStyle & PS_STYLE_MASK) != PS_INSIDEFRAME) &&
            ((dwPenStyle & PS_STYLE_MASK) != PS_USERSTYLE))
        {
            if (dwWidth == 0)
            {
                return FALSE;
            }
        }

        if (lbStyle == BS_NULL)
        {
            pelpExpect->elpPenStyle = PS_NULL;
            pelpExpect->elpWidth = 0;
            pelpExpect->elpBrushStyle = BS_SOLID;
            pelpExpect->elpColor = 0;
            pelpExpect->elpHatch = 0;
            pelpExpect->elpNumEntries = 0;
            return TRUE;
        }

        if (lbStyle > BS_HATCHED)
        {
            return FALSE;
        }

        if (lbStyle == BS_HATCHED)
        {
            if (lbHatch >= HS_API_MAX)
            {
                return FALSE;
            }
        }

    }

    pelpExpect->elpPenStyle = dwPenStyle;
    pelpExpect->elpWidth = dwWidth;
    pelpExpect->elpBrushStyle = lbStyle;
    pelpExpect->elpColor = RGB(1,2,3);
    pelpExpect->elpHatch = lbHatch;
    pelpExpect->elpNumEntries = dwStyleCount;
    //pelpExpect->elpStyleEntry[1];

    return TRUE;
}