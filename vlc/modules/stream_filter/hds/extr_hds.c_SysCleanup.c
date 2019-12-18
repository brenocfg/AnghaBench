#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t i_count; int /*<<< orphan*/ * pp_elems; } ;
struct TYPE_4__ {int /*<<< orphan*/  base_url; TYPE_2__ hds_streams; } ;
typedef  TYPE_1__ stream_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hds_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_array_clear (TYPE_2__*) ; 

__attribute__((used)) static void SysCleanup( stream_sys_t *p_sys )
{
    for( size_t i = 0; i < p_sys->hds_streams.i_count ; i++ )
        hds_free( p_sys->hds_streams.pp_elems[i] );
    vlc_array_clear( &p_sys->hds_streams );
    free( p_sys->base_url );
}