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
typedef  int /*<<< orphan*/  widget ;
struct TYPE_3__ {struct TYPE_3__* child; scalar_t__ enabled; } ;
typedef  TYPE_1__ container ;

/* Variables and functions */
 int /*<<< orphan*/  WIDGET (TYPE_1__*) ; 
 int /*<<< orphan*/  widget_move (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  widget_padding_get_left (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  widget_padding_get_remaining_height (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  widget_padding_get_remaining_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  widget_padding_get_top (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  widget_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void container_update ( widget *wid  )
{
    container *b = (container *) wid;
    if ( b->child && b->child->enabled ) {
        widget_resize ( WIDGET ( b->child ),
                        widget_padding_get_remaining_width  ( WIDGET ( b ) ),
                        widget_padding_get_remaining_height ( WIDGET ( b ) )
                        );
        widget_move ( WIDGET ( b->child ),
                      widget_padding_get_left ( WIDGET ( b ) ),
                      widget_padding_get_top ( WIDGET ( b ) )
                      );
    }
}