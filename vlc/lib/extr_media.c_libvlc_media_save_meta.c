#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {int /*<<< orphan*/  p_input_item; TYPE_1__* p_libvlc_instance; } ;
typedef  TYPE_2__ libvlc_media_t ;
struct TYPE_5__ {int /*<<< orphan*/  p_libvlc_int; } ;

/* Variables and functions */
 int /*<<< orphan*/ * VLC_OBJECT (int /*<<< orphan*/ ) ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 scalar_t__ input_item_WriteMeta (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int libvlc_media_save_meta( libvlc_media_t *p_md )
{
    assert( p_md );
    vlc_object_t *p_obj = VLC_OBJECT(p_md->p_libvlc_instance->p_libvlc_int);
    return input_item_WriteMeta( p_obj, p_md->p_input_item ) == VLC_SUCCESS;
}