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
typedef  int /*<<< orphan*/  widget ;
struct TYPE_2__ {scalar_t__ child; } ;
typedef  TYPE_1__ container ;

/* Variables and functions */
 scalar_t__ widget_get_desired_height (scalar_t__) ; 
 scalar_t__ widget_padding_get_padding_height (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int container_get_desired_height ( widget *widget )
{
    container *b     = (container *) widget;
    int       height = 0;
    if ( b->child ) {
        height += widget_get_desired_height ( b->child );
    }
    height += widget_padding_get_padding_height ( widget );
    return height;
}