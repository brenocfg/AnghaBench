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
struct TYPE_3__ {int tmHeight; } ;
typedef  TYPE_1__ TEXTMETRICA ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextMetricsA (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int font_height(HFONT hFont)
{
    TEXTMETRICA tm;
    HFONT hFontOld;
    HDC hDC;

    hDC = CreateCompatibleDC(NULL);
    hFontOld = SelectObject(hDC, hFont);
    GetTextMetricsA(hDC, &tm);
    SelectObject(hDC, hFontOld);
    DeleteDC(hDC);

    return tm.tmHeight;
}