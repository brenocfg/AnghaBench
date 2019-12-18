#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ptrdiff_t ;
struct TYPE_7__ {int i_planes; TYPE_1__* p; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_8__ {int displayed; TYPE_4__* buffer; } ;
typedef  TYPE_3__ picture_sys_t ;
struct TYPE_9__ {int data; } ;
struct TYPE_6__ {int p_pixels; int i_pitch; int i_lines; } ;
typedef  TYPE_4__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int VLC_SUCCESS ; 

int mmal_picture_lock(picture_t *picture)
{
    picture_sys_t *pic_sys = picture->p_sys;
    MMAL_BUFFER_HEADER_T *buffer = pic_sys->buffer;

    int offset = 0;
    picture->p[0].p_pixels = buffer->data;
    for (int i = 1; i < picture->i_planes; i++) {
        offset = offset + picture->p[i - 1].i_pitch * picture->p[i - 1].i_lines;
        picture->p[i].p_pixels = (ptrdiff_t)buffer->data + offset;
    }

    pic_sys->displayed = false;

    return VLC_SUCCESS;
}