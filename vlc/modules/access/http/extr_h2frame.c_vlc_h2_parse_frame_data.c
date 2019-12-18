#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_fast8_t ;
typedef  scalar_t__ uint_fast32_t ;
typedef  unsigned int uint8_t ;
struct vlc_h2_parser {size_t rcwd_size; TYPE_1__* cbs; int /*<<< orphan*/  opaque; } ;
struct vlc_h2_frame {int dummy; } ;
struct TYPE_2__ {int (* stream_data ) (void*,struct vlc_h2_frame*) ;int /*<<< orphan*/  (* stream_end ) (void*) ;int /*<<< orphan*/  (* window_status ) (int /*<<< orphan*/ ,size_t*) ;} ;

/* Variables and functions */
 int VLC_H2_DATA_END_STREAM ; 
 int VLC_H2_DATA_PADDED ; 
 int /*<<< orphan*/  VLC_H2_FLOW_CONTROL_ERROR ; 
 int /*<<< orphan*/  VLC_H2_FRAME_SIZE_ERROR ; 
 size_t VLC_H2_MAX_FRAME ; 
 int /*<<< orphan*/  VLC_H2_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  VLC_H2_STREAM_CLOSED ; 
 int /*<<< orphan*/  free (struct vlc_h2_frame*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,size_t*) ; 
 int stub2 (void*,struct vlc_h2_frame*) ; 
 int /*<<< orphan*/  stub3 (void*) ; 
 int vlc_h2_frame_flags (struct vlc_h2_frame*) ; 
 unsigned int* vlc_h2_frame_payload (struct vlc_h2_frame*) ; 
 int vlc_h2_parse_error (struct vlc_h2_parser*,int /*<<< orphan*/ ) ; 
 int vlc_h2_stream_error (struct vlc_h2_parser*,scalar_t__,int /*<<< orphan*/ ) ; 
 void* vlc_h2_stream_lookup (struct vlc_h2_parser*,scalar_t__) ; 

__attribute__((used)) static int vlc_h2_parse_frame_data(struct vlc_h2_parser *p,
                                   struct vlc_h2_frame *f, size_t len,
                                   uint_fast32_t id)
{
    uint_fast8_t flags = vlc_h2_frame_flags(f);
    const uint8_t *ptr = vlc_h2_frame_payload(f);

    if (id == 0)
    {
        free(f);
        return vlc_h2_parse_error(p, VLC_H2_PROTOCOL_ERROR);
    }

    if (len > VLC_H2_MAX_FRAME)
    {
        free(f);
        return vlc_h2_stream_error(p, id, VLC_H2_FRAME_SIZE_ERROR);
    }

    if (flags & VLC_H2_DATA_PADDED)
    {
        if (len < 1 || len < (1u + ptr[0]))
        {
            free(f);
            return vlc_h2_stream_error(p, id, VLC_H2_FRAME_SIZE_ERROR);
        }
        len -= 1 + ptr[0];
    }

    if (len > p->rcwd_size)
    {
        free(f);
        return vlc_h2_parse_error(p, VLC_H2_FLOW_CONTROL_ERROR);
    }

    p->rcwd_size -= len;
    p->cbs->window_status(p->opaque, &p->rcwd_size);

    void *s = vlc_h2_stream_lookup(p, id);
    if (s == NULL)
    {
        free(f);
        return vlc_h2_stream_error(p, id, VLC_H2_STREAM_CLOSED);
    }

    int ret = p->cbs->stream_data(s, f);
    /* Frame gets consumed here ^^ */

    if (flags & VLC_H2_DATA_END_STREAM)
        p->cbs->stream_end(s);
    return ret;
}