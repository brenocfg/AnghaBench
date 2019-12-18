#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  b_top_field_first; int /*<<< orphan*/  b_progressive; int /*<<< orphan*/  date; } ;
typedef  TYPE_1__ picture_t ;
struct TYPE_19__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_20__ {TYPE_6__* output_format; scalar_t__ opaque; int /*<<< orphan*/  sem; int /*<<< orphan*/  output_in_transit; scalar_t__ output_pool; int /*<<< orphan*/  b_top_field_first; int /*<<< orphan*/  b_progressive; } ;
typedef  TYPE_3__ decoder_sys_t ;
struct TYPE_24__ {scalar_t__ cmd; scalar_t__ length; int /*<<< orphan*/ * data; scalar_t__ alloc_size; int /*<<< orphan*/ * user_data; int /*<<< orphan*/  pts; } ;
struct TYPE_23__ {int /*<<< orphan*/  encoding; } ;
struct TYPE_22__ {int /*<<< orphan*/  format; } ;
struct TYPE_21__ {scalar_t__ userdata; } ;
typedef  TYPE_4__ MMAL_PORT_T ;
typedef  TYPE_5__ MMAL_EVENT_FORMAT_CHANGED_T ;
typedef  TYPE_6__ MMAL_ES_FORMAT_T ;
typedef  TYPE_7__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_ENCODING_OPAQUE ; 
 scalar_t__ MMAL_EVENT_FORMAT_CHANGED ; 
 int /*<<< orphan*/  atomic_fetch_sub (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  decoder_QueueVideo (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_7__*) ; 
 TYPE_5__* mmal_event_format_changed_get (TYPE_7__*) ; 
 TYPE_6__* mmal_format_alloc () ; 
 int /*<<< orphan*/  mmal_format_full_copy (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picture_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_sem_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void output_port_cb(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
    decoder_t *dec = (decoder_t *)port->userdata;
    decoder_sys_t *sys = dec->p_sys;
    picture_t *picture;
    MMAL_EVENT_FORMAT_CHANGED_T *fmt;
    MMAL_ES_FORMAT_T *format;

    if (buffer->cmd == 0) {
        picture = (picture_t *)buffer->user_data;
        if (buffer->length > 0) {
            picture->date = buffer->pts;
            picture->b_progressive = sys->b_progressive;
            picture->b_top_field_first = sys->b_top_field_first;
            decoder_QueueVideo(dec, picture);
        } else {
            picture_Release(picture);
            if (sys->output_pool) {
                buffer->user_data = NULL;
                buffer->alloc_size = 0;
                buffer->data = NULL;
                mmal_buffer_header_release(buffer);
            }
        }
        atomic_fetch_sub(&sys->output_in_transit, 1);
        vlc_sem_post(&sys->sem);
    } else if (buffer->cmd == MMAL_EVENT_FORMAT_CHANGED) {
        fmt = mmal_event_format_changed_get(buffer);

        format = mmal_format_alloc();
        mmal_format_full_copy(format, fmt->format);

        if (sys->opaque)
            format->encoding = MMAL_ENCODING_OPAQUE;

        sys->output_format = format;

        mmal_buffer_header_release(buffer);
    } else {
        mmal_buffer_header_release(buffer);
    }
}