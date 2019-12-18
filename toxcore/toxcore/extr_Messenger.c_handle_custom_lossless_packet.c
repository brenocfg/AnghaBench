#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  lossless_packethandler_userdata; int /*<<< orphan*/  (* lossless_packethandler ) (TYPE_1__*,int,scalar_t__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ Messenger ;

/* Variables and functions */
 scalar_t__ const PACKET_ID_LOSSLESS_RANGE_SIZE ; 
 scalar_t__ const PACKET_ID_LOSSLESS_RANGE_START ; 
 scalar_t__ friend_not_valid (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,scalar_t__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_custom_lossless_packet(void *object, int friend_num, const uint8_t *packet, uint16_t length)
{
    Messenger *m = object;

    if (friend_not_valid(m, friend_num))
        return -1;

    if (packet[0] < PACKET_ID_LOSSLESS_RANGE_START)
        return -1;

    if (packet[0] >= (PACKET_ID_LOSSLESS_RANGE_START + PACKET_ID_LOSSLESS_RANGE_SIZE))
        return -1;

    if (m->lossless_packethandler)
        m->lossless_packethandler(m, friend_num, packet, length, m->lossless_packethandler_userdata);

    return 1;
}