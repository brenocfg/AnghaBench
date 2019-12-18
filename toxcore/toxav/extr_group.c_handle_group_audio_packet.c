#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  sequnum ;
struct TYPE_8__ {int length; int* data; int /*<<< orphan*/  sequnum; } ;
struct TYPE_7__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ Group_Peer_AV ;
typedef  TYPE_2__ Group_Audio_Packet ;

/* Variables and functions */
 TYPE_2__* calloc (int,int) ; 
 scalar_t__ decode_audio_packet (void*,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ntohs (int) ; 
 int queue (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int handle_group_audio_packet(void *object, int groupnumber, int friendgroupnumber, void *peer_object,
                                     const uint8_t *packet, uint16_t length)
{
    if (!peer_object || !object || length <= sizeof(uint16_t)) {
        return -1;
    }

    Group_Peer_AV *peer_av = peer_object;

    Group_Audio_Packet *pk = calloc(1, sizeof(Group_Audio_Packet) + (length - sizeof(uint16_t)));

    if (!pk) {
        return -1;
    }

    uint16_t sequnum;
    memcpy(&sequnum, packet, sizeof(sequnum));
    pk->sequnum = ntohs(sequnum);
    pk->length = length - sizeof(uint16_t);
    memcpy(pk->data, packet + sizeof(uint16_t), length - sizeof(uint16_t));

    if (queue(peer_av->buffer, pk) == -1) {
        free(pk);
        return -1;
    }

    while (decode_audio_packet(object, peer_av, groupnumber, friendgroupnumber) == 0);

    return 0;
}