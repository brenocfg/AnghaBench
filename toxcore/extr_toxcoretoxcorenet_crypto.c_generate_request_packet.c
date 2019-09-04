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
typedef  size_t uint8_t ;
typedef  size_t uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {scalar_t__ buffer_start; scalar_t__ buffer_end; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ Packets_Array ;

/* Variables and functions */
 size_t CRYPTO_PACKET_BUFFER_SIZE ; 
 size_t PACKET_ID_REQUEST ; 

__attribute__((used)) static int generate_request_packet(uint8_t *data, uint16_t length, const Packets_Array *recv_array)
{
    if (length == 0)
        return -1;

    data[0] = PACKET_ID_REQUEST;

    uint16_t cur_len = 1;

    if (recv_array->buffer_start == recv_array->buffer_end)
        return cur_len;

    if (length <= cur_len)
        return cur_len;

    uint32_t i, n = 1;

    for (i = recv_array->buffer_start; i != recv_array->buffer_end; ++i) {
        uint32_t num = i % CRYPTO_PACKET_BUFFER_SIZE;

        if (!recv_array->buffer[num]) {
            data[cur_len] = n;
            n = 0;
            ++cur_len;

            if (length <= cur_len)
                return cur_len;

        } else if (n == 255) {
            data[cur_len] = 0;
            n = 0;
            ++cur_len;

            if (length <= cur_len)
                return cur_len;
        }

        ++n;
    }

    return cur_len;
}