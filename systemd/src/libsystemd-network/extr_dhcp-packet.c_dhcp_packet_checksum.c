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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,size_t) ; 

uint16_t dhcp_packet_checksum(uint8_t *buf, size_t len) {
        uint64_t *buf_64 = (uint64_t*)buf;
        uint64_t *end_64 = buf_64 + (len / sizeof(uint64_t));
        uint64_t sum = 0;

        /* See RFC1071 */

        while (buf_64 < end_64) {
                sum += *buf_64;
                if (sum < *buf_64)
                        /* wrap around in one's complement */
                        sum++;

                buf_64++;
        }

        if (len % sizeof(uint64_t)) {
                /* If the buffer is not aligned to 64-bit, we need
                   to zero-pad the last few bytes and add them in */
                uint64_t buf_tail = 0;

                memcpy(&buf_tail, buf_64, len % sizeof(uint64_t));

                sum += buf_tail;
                if (sum < buf_tail)
                        /* wrap around */
                        sum++;
        }

        while (sum >> 16)
                sum = (sum & 0xffff) + (sum >> 16);

        return ~sum;
}