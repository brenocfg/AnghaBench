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
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 unsigned int XIPH_MAX_HEADER_COUNT ; 
 int /*<<< orphan*/  assert (int) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const* const,unsigned int) ; 

__attribute__((used)) static inline int xiph_PackHeaders(int *extra_size, void **extra,
                                   unsigned packet_size[],
                                   const void *const packet[],
                                   unsigned packet_count)
{
    if (packet_count <= 0 || packet_count > XIPH_MAX_HEADER_COUNT)
        return VLC_EGENERIC;

    /* Compute the size needed for the whole extra data */
    unsigned payload_size = 0;
    unsigned header_size = 1;
    for (unsigned i = 0; i < packet_count; i++) {
        payload_size += packet_size[i];
        if (i < packet_count - 1)
            header_size += 1 + packet_size[i] / 255;
    }

    /* */
    *extra_size = header_size + payload_size;
    *extra = malloc(*extra_size);
    if (*extra == NULL)
        return VLC_ENOMEM;

    /* Write the header */
    uint8_t *current = (uint8_t*)*extra;
    *current++ = packet_count - 1;
    for (unsigned i = 0; i < packet_count - 1; i++) {
        unsigned t = packet_size[i];
        for (;;) {
            if (t >= 255) {
                *current++ = 255;
                t -= 255;
            } else {
                *current++ = t;
                break;
            }
        }
    }

    /* Copy the payloads */
    for (unsigned i = 0; i < packet_count; i++) {
        if (packet_size[i] > 0) {
            memcpy(current, packet[i], packet_size[i]);
            current += packet_size[i];
        }
    }
    assert(current == (uint8_t*)*extra + *extra_size);
    return VLC_SUCCESS;
}