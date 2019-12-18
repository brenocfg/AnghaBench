#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct discovery_sys {int /*<<< orphan*/  p_microdns; int /*<<< orphan*/  thread; int /*<<< orphan*/  stop; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (struct discovery_sys*) ; 
 int /*<<< orphan*/  items_clear (struct discovery_sys*) ; 
 int /*<<< orphan*/  mdns_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
CleanCommon( struct discovery_sys *p_sys )
{
    atomic_store( &p_sys->stop, true );
    vlc_join( p_sys->thread, NULL );

    items_clear( p_sys );
    mdns_destroy( p_sys->p_microdns );
    free( p_sys );
}