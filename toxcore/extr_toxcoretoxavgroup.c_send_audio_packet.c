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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  sequnum ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_3__ {int /*<<< orphan*/  audio_sequnum; } ;
typedef  int /*<<< orphan*/  Group_Chats ;
typedef  TYPE_1__ Group_AV ;

/* Variables and functions */
 int GROUP_AUDIO_PACKET_ID ; 
 TYPE_1__* group_get_object (int /*<<< orphan*/ *,int) ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int send_group_lossy_packet (int /*<<< orphan*/ *,int,int*,int) ; 

__attribute__((used)) static int send_audio_packet(Group_Chats *g_c, int groupnumber, uint8_t *packet, uint16_t length)
{
    if (!length)
        return -1;

    Group_AV *group_av = group_get_object(g_c, groupnumber);
    uint8_t data[1 + sizeof(uint16_t) + length];
    data[0] = GROUP_AUDIO_PACKET_ID;

    uint16_t sequnum = htons(group_av->audio_sequnum);
    memcpy(data + 1, &sequnum, sizeof(sequnum));
    memcpy(data + 1 + sizeof(sequnum), packet, length);

    if (send_group_lossy_packet(g_c, groupnumber, data, sizeof(data)) == -1)
        return -1;

    ++group_av->audio_sequnum;
    return 0;
}