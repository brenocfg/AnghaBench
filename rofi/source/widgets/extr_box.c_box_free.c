#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  widget ;
struct TYPE_7__ {int /*<<< orphan*/  children; } ;
typedef  TYPE_1__ box ;
struct TYPE_8__ {scalar_t__ data; } ;
typedef  TYPE_2__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 TYPE_2__* g_list_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_list_free (int /*<<< orphan*/ ) ; 
 TYPE_2__* g_list_next (TYPE_2__*) ; 
 int /*<<< orphan*/  widget_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void box_free ( widget *wid )
{
    box *b = (box *) wid;

    for ( GList *iter = g_list_first ( b->children ); iter != NULL; iter = g_list_next ( iter ) ) {
        widget * child = (widget *) iter->data;
        widget_free ( child );
    }
    g_list_free ( b->children );
    g_free ( b );
}