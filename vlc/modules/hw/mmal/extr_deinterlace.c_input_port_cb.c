#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_9__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_10__ {int /*<<< orphan*/  sem; int /*<<< orphan*/  input_in_transit; } ;
typedef  TYPE_2__ filter_sys_t ;
struct TYPE_12__ {scalar_t__ user_data; } ;
struct TYPE_11__ {scalar_t__ userdata; } ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_fetch_sub (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_4__*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void input_port_cb(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
    picture_t *picture = (picture_t *)buffer->user_data;
    filter_t *filter = (filter_t *)port->userdata;
    filter_sys_t *sys = filter->p_sys;

    if (picture) {
        picture_Release(picture);
    } else {
        msg_Warn(filter, "Got buffer without picture on input port - OOOPS");
        mmal_buffer_header_release(buffer);
    }

    atomic_fetch_sub(&sys->input_in_transit, 1);
    vlc_sem_post(&sys->sem);
}