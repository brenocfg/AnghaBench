#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int MarqueePos; int /*<<< orphan*/  Self; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ PROGRESS_INFO ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HTHEME ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_STYLE ; 
 int GetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowTheme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PBS_SMOOTH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdateWindow (int /*<<< orphan*/ ) ; 
 int get_bar_size (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_client_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int get_led_gap (TYPE_1__*) ; 
 int get_led_size (TYPE_1__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void PROGRESS_UpdateMarquee (PROGRESS_INFO *infoPtr)
{
    LONG style = GetWindowLongW (infoPtr->Self, GWL_STYLE);
    RECT rect;
    int ledWidth, leds;
    HTHEME theme = GetWindowTheme (infoPtr->Self);
    BOOL smooth = (style & PBS_SMOOTH) && !theme;

    get_client_rect (infoPtr->Self, &rect);

    if (smooth)
        ledWidth = 1;
    else
        ledWidth = get_led_size( infoPtr, style, &rect ) + get_led_gap( infoPtr );

    leds = (get_bar_size( style, &rect ) + ledWidth - 1) /
        ledWidth;

    /* increment the marquee progress */
    if (++infoPtr->MarqueePos >= leds)
        infoPtr->MarqueePos = 0;

    InvalidateRect(infoPtr->Self, &rect, TRUE);
    UpdateWindow(infoPtr->Self);
}