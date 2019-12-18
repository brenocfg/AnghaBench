#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sout_stream_id_sys_t ;
struct TYPE_8__ {unsigned int i_buffer; unsigned int i_length; int i_flags; unsigned int i_pts; unsigned int p_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_DISCONTINUITY ; 
 int VLC_ENOMEM ; 
 TYPE_1__* block_Alloc (int) ; 
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (unsigned int,unsigned int,unsigned int) ; 
 unsigned int rtp_mtu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtp_packetize_common (int /*<<< orphan*/ *,TYPE_1__*,int,unsigned int) ; 
 int /*<<< orphan*/  rtp_packetize_send (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int rtp_packetize_simple (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtp_packetize_pcm(sout_stream_id_sys_t *id, block_t *in)
{
    unsigned max = rtp_mtu(id);

    while (in->i_buffer > max)
    {
        unsigned duration = (in->i_length * max) / in->i_buffer;
        bool marker = (in->i_flags & BLOCK_FLAG_DISCONTINUITY) != 0;

        block_t *out = block_Alloc(12 + max);
        if (unlikely(out == NULL))
        {
            block_Release(in);
            return VLC_ENOMEM;
        }

        rtp_packetize_common(id, out, marker, in->i_pts);
        memcpy(out->p_buffer + 12, in->p_buffer, max);
        rtp_packetize_send(id, out);

        in->p_buffer += max;
        in->i_buffer -= max;
        in->i_pts += duration;
        in->i_length -= duration;
        in->i_flags &= ~BLOCK_FLAG_DISCONTINUITY;
    }

    return rtp_packetize_simple(id, in); /* zero copy for the last frame */
}