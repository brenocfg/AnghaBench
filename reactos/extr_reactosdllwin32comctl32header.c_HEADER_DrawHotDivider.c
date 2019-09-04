#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  clrHighlight; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  HEADER_INFO ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;

/* Variables and functions */
 int /*<<< orphan*/  CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEADER_GetHotDividerRect (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 TYPE_1__ comctl32_color ; 

__attribute__((used)) static void
HEADER_DrawHotDivider(const HEADER_INFO *infoPtr, HDC hdc)
{
    HBRUSH brush;
    RECT r;
    
    HEADER_GetHotDividerRect(infoPtr, &r);
    brush = CreateSolidBrush(comctl32_color.clrHighlight);
    FillRect(hdc, &r, brush);
    DeleteObject(brush);
}