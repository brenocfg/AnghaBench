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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  packet ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  Messenger ;

/* Variables and functions */
 unsigned int MAX_CRYPTO_DATA_SIZE ; 
 int /*<<< orphan*/  PACKET_ID_FILE_CONTROL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int write_cryptpacket_id (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int send_file_control_packet(const Messenger *m, int32_t friendnumber, uint8_t send_receive, uint8_t filenumber,
                             uint8_t control_type, uint8_t *data, uint16_t data_length)
{
    if ((unsigned int)(1 + 3 + data_length) > MAX_CRYPTO_DATA_SIZE)
        return -1;

    uint8_t packet[3 + data_length];

    packet[0] = send_receive;
    packet[1] = filenumber;
    packet[2] = control_type;

    if (data_length) {
        memcpy(packet + 3, data, data_length);
    }

    return write_cryptpacket_id(m, friendnumber, PACKET_ID_FILE_CONTROL, packet, sizeof(packet), 0);
}