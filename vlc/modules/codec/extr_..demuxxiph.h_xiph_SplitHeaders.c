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
typedef  unsigned int uint8_t ;

/* Variables and functions */
 unsigned int UINT_MAX ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 unsigned int xiph_CountHeaders (unsigned int const*,unsigned int) ; 

__attribute__((used)) static inline int xiph_SplitHeaders(unsigned packet_size[],
                                    const void *packet[], unsigned *packet_count,
                                    unsigned i_extra, const void *p_extra)
{
    const uint8_t *current = (const uint8_t *)p_extra;
    const uint8_t *end = &current[i_extra];
    if (i_extra < 1)
        return VLC_EGENERIC;

    /* Parse the packet count and their sizes */
    const unsigned count = xiph_CountHeaders(current, i_extra);
    if(count == 0)
        return VLC_EGENERIC;

    if (packet_count)
        *packet_count = count;

    /* - 1 byte (N-1) packets
     * - N-1 variable length payload sizes
     * - N-1 payloads
     * - Nth packet (remaining)  */

    /* skip count byte header */
    ++current;
    /* read sizes for N-1 packets */
    unsigned total_payload_minus_last = 0;
    for (unsigned i = 0; i < count - 1; i++)
    {
        packet_size[i] = 0;
        for (;;) {
            if (current >= end)
                return VLC_EGENERIC;
            packet_size[i] += *current;
            if (*current++ != 255)
                break;
        }
        if(UINT_MAX - total_payload_minus_last < packet_size[i])
            return VLC_EGENERIC;
        total_payload_minus_last += packet_size[i];
    }
    if(current + total_payload_minus_last > end)
        return VLC_EGENERIC;
    /* set pointers for N-1 packets */
    for (unsigned i = 0; i < count - 1; i++)
    {
        packet[i] = current;
        current += packet_size[i];
    }
    /* Last packet is remaining size */
    packet_size[count - 1] = end - current;
    packet[count - 1] = current;

    return VLC_SUCCESS;
}