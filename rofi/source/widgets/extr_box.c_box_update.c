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
struct TYPE_6__ {scalar_t__ parent; } ;
typedef  TYPE_1__ widget ;
struct TYPE_7__ {int type; } ;
typedef  TYPE_2__ box ;

/* Variables and functions */
#define  ROFI_ORIENTATION_HORIZONTAL 129 
#define  ROFI_ORIENTATION_VERTICAL 128 
 int /*<<< orphan*/  hori_calculate_size (TYPE_2__*) ; 
 int /*<<< orphan*/  vert_calculate_size (TYPE_2__*) ; 
 int /*<<< orphan*/  widget_update (scalar_t__) ; 

__attribute__((used)) static void box_update ( widget *wid  )
{
    box *b = (box *) wid;
    switch ( b->type )
    {
    case ROFI_ORIENTATION_VERTICAL:
        vert_calculate_size ( b );
        break;
    case ROFI_ORIENTATION_HORIZONTAL:
    default:
        hori_calculate_size ( b );
    }
    if ( wid->parent ) {
        widget_update ( wid->parent );
    }
}