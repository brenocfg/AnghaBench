#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ m_bytes_in_buffer; scalar_t__ (* m_write_fn ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  m_stored_data; int /*<<< orphan*/  m_current_data; int /*<<< orphan*/  m_status; int /*<<< orphan*/  m_user_data; } ;
typedef  TYPE_1__ opj_stream_private_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
typedef  scalar_t__ OPJ_SIZE_T ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_INFO ; 
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_STREAM_STATUS_ERROR ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

OPJ_BOOL opj_stream_flush(opj_stream_private_t * p_stream,
                          opj_event_mgr_t * p_event_mgr)
{
    /* the number of bytes written on the media. */
    OPJ_SIZE_T l_current_write_nb_bytes = 0;

    p_stream->m_current_data = p_stream->m_stored_data;

    while (p_stream->m_bytes_in_buffer) {
        /* we should do an actual write on the media */
        l_current_write_nb_bytes = p_stream->m_write_fn(p_stream->m_current_data,
                                   p_stream->m_bytes_in_buffer,
                                   p_stream->m_user_data);

        if (l_current_write_nb_bytes == (OPJ_SIZE_T) - 1) {
            p_stream->m_status |= OPJ_STREAM_STATUS_ERROR;
            opj_event_msg(p_event_mgr, EVT_INFO, "Error on writing stream!\n");

            return OPJ_FALSE;
        }

        p_stream->m_current_data += l_current_write_nb_bytes;
        p_stream->m_bytes_in_buffer -= l_current_write_nb_bytes;
    }

    p_stream->m_current_data = p_stream->m_stored_data;

    return OPJ_TRUE;
}