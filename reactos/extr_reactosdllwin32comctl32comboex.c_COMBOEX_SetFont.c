#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_4__ {scalar_t__ hwndCombo; scalar_t__ hwndEdit; scalar_t__ font; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ HFONT ;
typedef  TYPE_1__ COMBOEX_INFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  COMBOEX_ReSize (TYPE_1__*) ; 
 int /*<<< orphan*/  InvalidateRect (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_SETFONT ; 

__attribute__((used)) static LRESULT COMBOEX_SetFont( COMBOEX_INFO *infoPtr, HFONT font, BOOL redraw )
{
    infoPtr->font = font;
    SendMessageW( infoPtr->hwndCombo, WM_SETFONT, (WPARAM)font, 0 );
    if (infoPtr->hwndEdit) SendMessageW( infoPtr->hwndEdit, WM_SETFONT, (WPARAM)font, 0 );
    COMBOEX_ReSize( infoPtr );
    if (redraw) InvalidateRect( infoPtr->hwndCombo, NULL, TRUE );
    return 0;
}