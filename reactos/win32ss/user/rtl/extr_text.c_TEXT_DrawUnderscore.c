#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {int right; int left; int top; int bottom; } ;
struct TYPE_6__ {int cx; } ;
typedef  TYPE_1__ SIZE ;
typedef  TYPE_2__ RECT ;
typedef  int /*<<< orphan*/  HPEN ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CreatePen (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextExtentPointW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  GreDeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GreGetTextColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GreGetTextExtentW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GreMoveTo (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  MoveToEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtGdiCreatePen (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtGdiLineTo (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  NtGdiSelectPen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PS_SOLID ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void TEXT_DrawUnderscore (HDC hdc, int x, int y, const WCHAR *str, int offset, const RECT *rect)
{
    int prefix_x;
    int prefix_end;
    SIZE size;
    HPEN hpen;
    HPEN oldPen;
#ifdef _WIN32K_
    GreGetTextExtentW (hdc, str, offset, &size, 0);
#else
    GetTextExtentPointW (hdc, str, offset, &size);
#endif
    prefix_x = x + size.cx;
#ifdef _WIN32K_
    GreGetTextExtentW (hdc, str, offset+1, &size, 0);
#else
    GetTextExtentPointW (hdc, str, offset+1, &size);
#endif
    prefix_end = x + size.cx - 1;
    /* The above method may eventually be slightly wrong due to kerning etc. */

    /* Check for clipping */
    if (rect)
    {
        if (prefix_x > rect->right || prefix_end < rect->left ||
            y < rect->top || y > rect->bottom)
            return; /* Completely outside */
        /* Partially outside */
        if (prefix_x   < rect->left ) prefix_x   = rect->left;
        if (prefix_end > rect->right) prefix_end = rect->right;
    }
#ifdef _WIN32K_
    hpen = NtGdiCreatePen (PS_SOLID, 1, GreGetTextColor (hdc), NULL);
    oldPen = NtGdiSelectPen (hdc, hpen);
    GreMoveTo (hdc, prefix_x, y, NULL);
    NtGdiLineTo (hdc, prefix_end, y);
    NtGdiSelectPen (hdc, oldPen);
    GreDeleteObject (hpen);
#else
    hpen = CreatePen (PS_SOLID, 1, GetTextColor (hdc));
    oldPen = SelectObject (hdc, hpen);
    MoveToEx (hdc, prefix_x, y, NULL);
    LineTo (hdc, prefix_end, y);
    SelectObject (hdc, oldPen);
    DeleteObject (hpen);
#endif
}