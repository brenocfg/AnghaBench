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
struct TYPE_7__ {int monitor_id; struct TYPE_7__* next; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_2__ workarea ;
struct TYPE_8__ {TYPE_2__* monitors; TYPE_1__* screen; } ;
struct TYPE_6__ {int /*<<< orphan*/  height_in_pixels; int /*<<< orphan*/  width_in_pixels; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* xcb ; 

__attribute__((used)) static int monitor_get_dimension ( int monitor_id, workarea *mon )
{
    memset ( mon, 0, sizeof ( workarea ) );
    mon->w = xcb->screen->width_in_pixels;
    mon->h = xcb->screen->height_in_pixels;

    workarea *iter = NULL;
    for ( iter = xcb->monitors; iter; iter = iter->next ) {
        if ( iter->monitor_id == monitor_id ) {
            *mon = *iter;
            return TRUE;
        }
    }
    return FALSE;
}