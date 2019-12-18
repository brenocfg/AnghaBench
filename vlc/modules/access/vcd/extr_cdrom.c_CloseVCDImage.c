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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  p_sectors; } ;
struct TYPE_5__ {int i_vcdimage_handle; TYPE_1__ toc; } ;
typedef  TYPE_2__ vcddev_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_close (int) ; 

__attribute__((used)) static void CloseVCDImage( vlc_object_t * p_this, vcddev_t *p_vcddev )
{
    VLC_UNUSED( p_this );
    if( p_vcddev->i_vcdimage_handle != -1 )
        vlc_close( p_vcddev->i_vcdimage_handle );
    else
        return;

    free( p_vcddev->toc.p_sectors );
}