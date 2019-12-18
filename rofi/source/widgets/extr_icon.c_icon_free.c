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
struct TYPE_3__ {scalar_t__ icon; } ;
typedef  TYPE_1__ icon ;

/* Variables and functions */
 int /*<<< orphan*/  cairo_surface_destroy (scalar_t__) ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 

__attribute__((used)) static void icon_free ( widget *wid )
{
    icon *b = (icon *) wid;

    if ( b->icon ) {
        cairo_surface_destroy ( b->icon );
    }

    g_free ( b );
}