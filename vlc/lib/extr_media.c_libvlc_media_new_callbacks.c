#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  p_input_item; } ;
typedef  TYPE_1__ libvlc_media_t ;
typedef  void* libvlc_media_seek_cb ;
typedef  void* libvlc_media_read_cb ;
typedef  void* libvlc_media_open_cb ;
typedef  void* libvlc_media_close_cb ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_item_AddOpaque (int /*<<< orphan*/ ,char*,void*) ; 
 TYPE_1__* libvlc_media_new_location (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

libvlc_media_t *libvlc_media_new_callbacks(libvlc_instance_t *p_instance,
                                           libvlc_media_open_cb open_cb,
                                           libvlc_media_read_cb read_cb,
                                           libvlc_media_seek_cb seek_cb,
                                           libvlc_media_close_cb close_cb,
                                           void *opaque)
{
    libvlc_media_t *m = libvlc_media_new_location(p_instance, "imem://");
    if (unlikely(m == NULL))
        return NULL;

    assert(read_cb != NULL);
    input_item_AddOpaque(m->p_input_item, "imem-data", opaque);
    input_item_AddOpaque(m->p_input_item, "imem-open", open_cb);
    input_item_AddOpaque(m->p_input_item, "imem-read", read_cb);
    input_item_AddOpaque(m->p_input_item, "imem-seek", seek_cb);
    input_item_AddOpaque(m->p_input_item, "imem-close", close_cb);
    return m;
}