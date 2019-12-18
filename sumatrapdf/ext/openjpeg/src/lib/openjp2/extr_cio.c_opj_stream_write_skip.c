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
struct TYPE_4__ {int m_status; scalar_t__ (* m_skip_fn ) (scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  m_byte_offset; int /*<<< orphan*/  m_user_data; scalar_t__ m_bytes_in_buffer; } ;
typedef  TYPE_1__ opj_stream_private_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
typedef  scalar_t__ OPJ_OFF_T ;
typedef  scalar_t__ OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_INFO ; 
 int OPJ_STREAM_STATUS_ERROR ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ opj_stream_flush (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (scalar_t__,int /*<<< orphan*/ ) ; 

OPJ_OFF_T opj_stream_write_skip(opj_stream_private_t * p_stream,
                                OPJ_OFF_T p_size, opj_event_mgr_t * p_event_mgr)
{
    OPJ_BOOL l_is_written = 0;
    OPJ_OFF_T l_current_skip_nb_bytes = 0;
    OPJ_OFF_T l_skip_nb_bytes = 0;

    if (p_stream->m_status & OPJ_STREAM_STATUS_ERROR) {
        return (OPJ_OFF_T) - 1;
    }

    /* we should flush data */
    l_is_written = opj_stream_flush(p_stream, p_event_mgr);
    if (! l_is_written) {
        p_stream->m_status |= OPJ_STREAM_STATUS_ERROR;
        p_stream->m_bytes_in_buffer = 0;
        return (OPJ_OFF_T) - 1;
    }
    /* then skip */

    while (p_size > 0) {
        /* we should do an actual skip on the media */
        l_current_skip_nb_bytes = p_stream->m_skip_fn(p_size, p_stream->m_user_data);

        if (l_current_skip_nb_bytes == (OPJ_OFF_T) - 1) {
            opj_event_msg(p_event_mgr, EVT_INFO, "Stream error!\n");

            p_stream->m_status |= OPJ_STREAM_STATUS_ERROR;
            p_stream->m_byte_offset += l_skip_nb_bytes;
            /* end if stream */
            return l_skip_nb_bytes ? l_skip_nb_bytes : (OPJ_OFF_T) - 1;
        }
        p_size -= l_current_skip_nb_bytes;
        l_skip_nb_bytes += l_current_skip_nb_bytes;
    }

    p_stream->m_byte_offset += l_skip_nb_bytes;

    return l_skip_nb_bytes;
}