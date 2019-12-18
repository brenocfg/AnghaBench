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
struct TYPE_3__ {scalar_t__ m_bytes_in_buffer; int m_status; scalar_t__ m_buffer_size; scalar_t__ (* m_read_fn ) (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * m_stored_data; int /*<<< orphan*/ * m_current_data; int /*<<< orphan*/  m_byte_offset; int /*<<< orphan*/  m_user_data; } ;
typedef  TYPE_1__ opj_stream_private_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
typedef  scalar_t__ OPJ_SIZE_T ;
typedef  scalar_t__ OPJ_OFF_T ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_INFO ; 
 int OPJ_STREAM_STATUS_END ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

OPJ_SIZE_T opj_stream_read_data(opj_stream_private_t * p_stream,
                                OPJ_BYTE * p_buffer, OPJ_SIZE_T p_size, opj_event_mgr_t * p_event_mgr)
{
    OPJ_SIZE_T l_read_nb_bytes = 0;
    if (p_stream->m_bytes_in_buffer >= p_size) {
        memcpy(p_buffer, p_stream->m_current_data, p_size);
        p_stream->m_current_data += p_size;
        p_stream->m_bytes_in_buffer -= p_size;
        l_read_nb_bytes += p_size;
        p_stream->m_byte_offset += (OPJ_OFF_T)p_size;
        return l_read_nb_bytes;
    }

    /* we are now in the case when the remaining data if not sufficient */
    if (p_stream->m_status & OPJ_STREAM_STATUS_END) {
        l_read_nb_bytes += p_stream->m_bytes_in_buffer;
        memcpy(p_buffer, p_stream->m_current_data, p_stream->m_bytes_in_buffer);
        p_stream->m_current_data += p_stream->m_bytes_in_buffer;
        p_stream->m_byte_offset += (OPJ_OFF_T)p_stream->m_bytes_in_buffer;
        p_stream->m_bytes_in_buffer = 0;
        return l_read_nb_bytes ? l_read_nb_bytes : (OPJ_SIZE_T) - 1;
    }

    /* the flag is not set, we copy data and then do an actual read on the stream */
    if (p_stream->m_bytes_in_buffer) {
        l_read_nb_bytes += p_stream->m_bytes_in_buffer;
        memcpy(p_buffer, p_stream->m_current_data, p_stream->m_bytes_in_buffer);
        p_stream->m_current_data = p_stream->m_stored_data;
        p_buffer += p_stream->m_bytes_in_buffer;
        p_size -= p_stream->m_bytes_in_buffer;
        p_stream->m_byte_offset += (OPJ_OFF_T)p_stream->m_bytes_in_buffer;
        p_stream->m_bytes_in_buffer = 0;
    } else {
        /* case where we are already at the end of the buffer
           so reset the m_current_data to point to the start of the
           stored buffer to get ready to read from disk*/
        p_stream->m_current_data = p_stream->m_stored_data;
    }

    for (;;) {
        /* we should read less than a chunk -> read a chunk */
        if (p_size < p_stream->m_buffer_size) {
            /* we should do an actual read on the media */
            p_stream->m_bytes_in_buffer = p_stream->m_read_fn(p_stream->m_stored_data,
                                          p_stream->m_buffer_size, p_stream->m_user_data);

            if (p_stream->m_bytes_in_buffer == (OPJ_SIZE_T) - 1) {
                /* end of stream */
                opj_event_msg(p_event_mgr, EVT_INFO, "Stream reached its end !\n");

                p_stream->m_bytes_in_buffer = 0;
                p_stream->m_status |= OPJ_STREAM_STATUS_END;
                /* end of stream */
                return l_read_nb_bytes ? l_read_nb_bytes : (OPJ_SIZE_T) - 1;
            } else if (p_stream->m_bytes_in_buffer < p_size) {
                /* not enough data */
                l_read_nb_bytes += p_stream->m_bytes_in_buffer;
                memcpy(p_buffer, p_stream->m_current_data, p_stream->m_bytes_in_buffer);
                p_stream->m_current_data = p_stream->m_stored_data;
                p_buffer += p_stream->m_bytes_in_buffer;
                p_size -= p_stream->m_bytes_in_buffer;
                p_stream->m_byte_offset += (OPJ_OFF_T)p_stream->m_bytes_in_buffer;
                p_stream->m_bytes_in_buffer = 0;
            } else {
                l_read_nb_bytes += p_size;
                memcpy(p_buffer, p_stream->m_current_data, p_size);
                p_stream->m_current_data += p_size;
                p_stream->m_bytes_in_buffer -= p_size;
                p_stream->m_byte_offset += (OPJ_OFF_T)p_size;
                return l_read_nb_bytes;
            }
        } else {
            /* direct read on the dest buffer */
            p_stream->m_bytes_in_buffer = p_stream->m_read_fn(p_buffer, p_size,
                                          p_stream->m_user_data);

            if (p_stream->m_bytes_in_buffer == (OPJ_SIZE_T) - 1) {
                /*  end of stream */
                opj_event_msg(p_event_mgr, EVT_INFO, "Stream reached its end !\n");

                p_stream->m_bytes_in_buffer = 0;
                p_stream->m_status |= OPJ_STREAM_STATUS_END;
                /* end of stream */
                return l_read_nb_bytes ? l_read_nb_bytes : (OPJ_SIZE_T) - 1;
            } else if (p_stream->m_bytes_in_buffer < p_size) {
                /* not enough data */
                l_read_nb_bytes += p_stream->m_bytes_in_buffer;
                p_stream->m_current_data = p_stream->m_stored_data;
                p_buffer += p_stream->m_bytes_in_buffer;
                p_size -= p_stream->m_bytes_in_buffer;
                p_stream->m_byte_offset += (OPJ_OFF_T)p_stream->m_bytes_in_buffer;
                p_stream->m_bytes_in_buffer = 0;
            } else {
                /* we have read the exact size */
                l_read_nb_bytes += p_stream->m_bytes_in_buffer;
                p_stream->m_byte_offset += (OPJ_OFF_T)p_stream->m_bytes_in_buffer;
                p_stream->m_current_data = p_stream->m_stored_data;
                p_stream->m_bytes_in_buffer = 0;
                return l_read_nb_bytes;
            }
        }
    }
}