#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int XIPH_MAX_HEADER_COUNT ; 
 int* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int*,void const*,unsigned int) ; 
 scalar_t__ xiph_SplitHeaders (unsigned int*,void const**,unsigned int*,size_t,void*) ; 

__attribute__((used)) static int rtp_xiph_pack_headers(size_t room, void *p_extra, size_t i_extra,
                                 uint8_t **p_buffer, size_t *i_buffer,
                                 uint8_t *theora_pixel_fmt)
{
    unsigned packet_size[XIPH_MAX_HEADER_COUNT];
    const void *packet[XIPH_MAX_HEADER_COUNT];
    unsigned packet_count;

    if (xiph_SplitHeaders(packet_size, packet, &packet_count,
                                i_extra, p_extra))
        return VLC_EGENERIC;;
    if (packet_count < 3)
        return VLC_EGENERIC;;

    if (theora_pixel_fmt != NULL)
    {
        if (packet_size[0] < 42)
            return VLC_EGENERIC;
        *theora_pixel_fmt = (((const uint8_t *)packet[0])[41] >> 3) & 0x03;
    }

    unsigned length_size[2] = { 0, 0 };
    for (int i = 0; i < 2; i++)
    {
        unsigned size = packet_size[i];
        while (size > 0)
        {
            length_size[i]++;
            size >>= 7;
        }
    }

    *i_buffer = room + 1 + length_size[0] + length_size[1]
                + packet_size[0] + packet_size[1] + packet_size[2];
    *p_buffer = malloc(*i_buffer);
    if (*p_buffer == NULL)
        return VLC_ENOMEM;

    uint8_t *p = *p_buffer + room;
    /* Number of headers */
    *p++ = 2;

    for (int i = 0; i < 2; i++)
    {
        unsigned size = length_size[i];
        while (size > 0)
        {
            *p = (packet_size[i] >> (7 * (size - 1))) & 0x7f;
            if (--size > 0)
                *p |= 0x80;
            p++;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        memcpy(p, packet[i], packet_size[i]);
        p += packet_size[i];
    }

    return VLC_SUCCESS;
}