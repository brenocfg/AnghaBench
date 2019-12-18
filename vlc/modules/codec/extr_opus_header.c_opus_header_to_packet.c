#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned char channels; unsigned char channel_mapping; unsigned char nb_streams; unsigned char nb_coupled; unsigned char* stream_map; int /*<<< orphan*/  gain; int /*<<< orphan*/  input_sample_rate; int /*<<< orphan*/  preskip; } ;
struct TYPE_7__ {unsigned char* data; int maxlen; int pos; } ;
typedef  TYPE_1__ Packet ;
typedef  TYPE_2__ OpusHeader ;

/* Variables and functions */
 int /*<<< orphan*/  write_chars (TYPE_1__*,unsigned char const*,int) ; 
 int /*<<< orphan*/  write_uint16 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_uint32 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opus_header_to_packet(const OpusHeader *h, unsigned char *packet, int len)
{
    Packet p;
    unsigned char ch;

    p.data = packet;
    p.maxlen = len;
    p.pos = 0;
    if (len<19)return 0;
    if (!write_chars(&p, (const unsigned char*)"OpusHead", 8))
        return 0;
    /* Version is 1 */
    ch = 1;
    if (!write_chars(&p, &ch, 1))
        return 0;

    ch = h->channels;
    if (!write_chars(&p, &ch, 1))
        return 0;

    if (!write_uint16(&p, h->preskip))
        return 0;

    if (!write_uint32(&p, h->input_sample_rate))
        return 0;

    if (!write_uint16(&p, h->gain))
        return 0;

    ch = h->channel_mapping;
    if (!write_chars(&p, &ch, 1))
        return 0;

    if (h->channel_mapping != 0)
    {
        ch = h->nb_streams;
        if (!write_chars(&p, &ch, 1))
            return 0;

        ch = h->nb_coupled;
        if (!write_chars(&p, &ch, 1))
            return 0;

        /* Multi-stream support */
        for (int i=0;i<h->channels;i++)
        {
            if (!write_chars(&p, &h->stream_map[i], 1))
                return 0;
        }
    }

    return p.pos;
}