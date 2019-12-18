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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int rand () ; 

uint32_t create_packet(uint8_t *packet, uint8_t *string, uint8_t str_len, uint8_t id)
{
    memset(packet, 0, str_len + 13 + 16);
    packet[0] = id;
    packet[1] = rand();
    packet[5] = 1;
    packet[11] = 1;
    packet[12] = '.';
    memcpy(packet + 13, string, str_len);
    uint32_t i, c = 0;

    for (i = str_len + 12; i != 11; --i) {
        if (packet[i] == '.') {
            packet[i] = c;
            c = 0;
        } else {
            ++c;
        }
    }

    packet[str_len + 13 + 2] = 16;
    packet[str_len + 13 + 4] = 1;
    packet[str_len + 13 + 7] = 0x29;
    packet[str_len + 13 + 8] = 16;
    packet[str_len + 13 + 12] = 0x80;
    return str_len + 13 + 16;
}