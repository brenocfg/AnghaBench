#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; struct TYPE_7__* next; } ;
typedef  TYPE_2__ workarea ;
struct TYPE_8__ {TYPE_2__* monitors; TYPE_1__* screen; } ;
struct TYPE_6__ {int /*<<< orphan*/  height_in_pixels; int /*<<< orphan*/  width_in_pixels; } ;

/* Variables and functions */
 scalar_t__ INTERSECT (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* xcb ; 

__attribute__((used)) static void monitor_dimensions ( int x, int y, workarea *mon )
{
    memset ( mon, 0, sizeof ( workarea ) );
    mon->w = xcb->screen->width_in_pixels;
    mon->h = xcb->screen->height_in_pixels;

    for ( workarea *iter = xcb->monitors; iter; iter = iter->next ) {
        if ( INTERSECT ( x, y, iter->x, iter->y, iter->w, iter->h ) ) {
            *mon = *iter;
            break;
        }
    }
}