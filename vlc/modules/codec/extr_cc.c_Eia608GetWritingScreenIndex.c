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
struct TYPE_3__ {int mode; int i_screen; } ;
typedef  TYPE_1__ eia608_t ;

/* Variables and functions */
#define  EIA608_MODE_PAINTON 132 
#define  EIA608_MODE_POPUP 131 
#define  EIA608_MODE_ROLLUP_2 130 
#define  EIA608_MODE_ROLLUP_3 129 
#define  EIA608_MODE_ROLLUP_4 128 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static int Eia608GetWritingScreenIndex( eia608_t *h )
{
    switch( h->mode )
    {
    case EIA608_MODE_POPUP:    // Non displayed screen
        return 1 - h->i_screen;

    case EIA608_MODE_ROLLUP_2: // Displayed screen
    case EIA608_MODE_ROLLUP_3:
    case EIA608_MODE_ROLLUP_4:
    case EIA608_MODE_PAINTON:
        return h->i_screen;
    default:
        /* It cannot happen, else it is a bug */
        vlc_assert_unreachable();
        return 0;
    }
}