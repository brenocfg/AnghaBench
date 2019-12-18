#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ distance; } ;
struct TYPE_7__ {TYPE_1__ top; } ;
struct TYPE_8__ {int h; TYPE_2__ border; } ;
struct TYPE_9__ {int length; TYPE_3__ widget; scalar_t__ pos_length; } ;
typedef  TYPE_4__ scrollbar ;
typedef  int guint ;

/* Variables and functions */
 unsigned int MAX (int /*<<< orphan*/ ,int) ; 
 int MIN (unsigned int,int) ; 

guint scrollbar_scroll_get_line ( const scrollbar *sb, int y )
{
    y -= sb->widget.border.top.distance;
    if ( y < 0 ) {
        return 0;
    }

    if ( y > sb->widget.h ) {
        return sb->length - 1;
    }

    short  r           = ( sb->length * sb->widget.h ) / ( (double) ( sb->length + sb->pos_length ) );
    short  handle      = sb->widget.h - r;
    double sec         = ( ( r ) / (double) ( sb->length - 1 ) );
    short  half_handle = handle / 2;
    y -= half_handle;
    y  = MIN ( MAX ( 0, y ), sb->widget.h - 2 * half_handle );

    unsigned int sel = ( ( y ) / sec );
    return MIN ( sel, sb->length - 1 );
}