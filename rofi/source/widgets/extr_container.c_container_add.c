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
struct TYPE_7__ {TYPE_1__* child; } ;
typedef  TYPE_2__ container ;

/* Variables and functions */
 scalar_t__ WIDGET (TYPE_2__*) ; 
 int /*<<< orphan*/  g_assert (int) ; 
 int /*<<< orphan*/  widget_update (scalar_t__) ; 

void container_add ( container *container, widget *child )
{
    if ( container == NULL ) {
        return;
    }
    container->child = child;
    g_assert ( child->parent == WIDGET ( container  ) );
    widget_update ( WIDGET ( container ) );
}