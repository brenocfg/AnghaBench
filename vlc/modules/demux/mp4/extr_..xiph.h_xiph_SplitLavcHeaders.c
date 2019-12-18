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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 unsigned int GetWBE (int /*<<< orphan*/  const*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 unsigned int xiph_CountLavcHeaders (int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static inline int xiph_SplitLavcHeaders(unsigned packet_size[],
                                        const void *packet[], unsigned *packet_count,
                                        unsigned i_extra, const void *p_extra)
{
    const uint8_t *current = (const uint8_t *)p_extra;
    const uint8_t *end = &current[i_extra];
    if (i_extra < 2)
        return VLC_EGENERIC;
    /* Parse the packet count and their sizes */
    const unsigned count = xiph_CountLavcHeaders(current, i_extra);
    if(count == 0)
        return VLC_EGENERIC;
    if (packet_count)
        *packet_count = count;
    /* count is trusted here (xiph_CountHeaders) */
    for (unsigned i=0; i < count; i++)
    {
        /* each payload is prefixed by word size */
        packet_size[i] = GetWBE(current);
        if(&current[2U + packet_size[i]] > end)
            return VLC_EGENERIC;
        packet[i] = current + 2;
        current += packet_size[i] + 2;
    }
    return VLC_SUCCESS;
}