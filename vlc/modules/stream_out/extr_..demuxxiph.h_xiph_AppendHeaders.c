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

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int XIPH_MAX_HEADER_COUNT ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ xiph_PackHeaders (int*,void**,unsigned int*,void const**,unsigned int) ; 
 scalar_t__ xiph_SplitHeaders (unsigned int*,void const**,unsigned int*,int,void*) ; 

__attribute__((used)) static inline int xiph_AppendHeaders(int *extra_size, void **extra,
                                     unsigned size, const void *data)
{
    unsigned packet_size[XIPH_MAX_HEADER_COUNT];
    const void *packet[XIPH_MAX_HEADER_COUNT];
    unsigned count;

    if (*extra_size > 0 && *extra) {
        if (xiph_SplitHeaders(packet_size, packet, &count, *extra_size, *extra))
            return VLC_EGENERIC;
    } else {
        count = 0;
    }
    if (count >= XIPH_MAX_HEADER_COUNT)
        return VLC_EGENERIC;

    void *old = *extra;

    packet_size[count] = size;
    packet[count]      = (void*)data;
    if (xiph_PackHeaders(extra_size, extra, packet_size,
                         packet, count + 1)) {
        *extra_size = 0;
        *extra      = NULL;
    }

    free(old);

    if (*extra_size <= 0)
        return VLC_EGENERIC;
    return VLC_SUCCESS;
}