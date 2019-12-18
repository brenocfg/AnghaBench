#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gpointer ;
struct TYPE_9__ {scalar_t__ data; } ;
struct TYPE_8__ {int /*<<< orphan*/  sizes; int /*<<< orphan*/  surface; struct TYPE_8__* name; } ;
typedef  TYPE_1__ IconFetcherNameEntry ;
typedef  TYPE_1__ IconFetcherEntry ;
typedef  TYPE_3__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 TYPE_3__* g_list_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_list_free (int /*<<< orphan*/ ) ; 
 TYPE_3__* g_list_next (TYPE_3__*) ; 

__attribute__((used)) static void rofi_icon_fetch_entry_free ( gpointer data )
{
    IconFetcherNameEntry *entry = (IconFetcherNameEntry *) data;

    // Free name/key.
    g_free ( entry->name );

    for ( GList *iter = g_list_first ( entry->sizes ); iter; iter = g_list_next ( iter ) ) {
        IconFetcherEntry *sentry = (IconFetcherEntry *) ( iter->data );

        cairo_surface_destroy ( sentry->surface );
        g_free ( sentry );
    }

    g_list_free ( entry->sizes );
    g_free ( entry );
}