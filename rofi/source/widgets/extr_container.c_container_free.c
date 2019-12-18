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
struct TYPE_3__ {int /*<<< orphan*/  child; } ;
typedef  TYPE_1__ container ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  widget_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void container_free ( widget *wid )
{
    container *b = (container *) wid;

    widget_free ( b->child );
    g_free ( b );
}