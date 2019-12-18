#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {TYPE_1__* group; } ;
struct TYPE_4__ {int bottom_lossy_number; int top_lossy_number; int* recv_lossy; } ;
typedef  TYPE_2__ Group_c ;

/* Variables and functions */
 int MAX_LOSSY_COUNT ; 
 int /*<<< orphan*/  sodium_memzero (int*,int) ; 

__attribute__((used)) static unsigned int lossy_packet_not_received(Group_c *g, int peer_index, uint16_t message_number)
{
    if (peer_index == -1)
        return -1;

    if (g->group[peer_index].bottom_lossy_number == g->group[peer_index].top_lossy_number) {
        g->group[peer_index].top_lossy_number = message_number;
        g->group[peer_index].bottom_lossy_number = (message_number - MAX_LOSSY_COUNT) + 1;
        g->group[peer_index].recv_lossy[message_number % MAX_LOSSY_COUNT] = 1;
        return 0;
    }

    if ((uint16_t)(message_number - g->group[peer_index].bottom_lossy_number) < MAX_LOSSY_COUNT) {
        if (g->group[peer_index].recv_lossy[message_number % MAX_LOSSY_COUNT]) {
            return 1;
        }

        g->group[peer_index].recv_lossy[message_number % MAX_LOSSY_COUNT] = 1;
        return 0;
    }

    if ((uint16_t)(message_number - g->group[peer_index].bottom_lossy_number) > (1 << 15))
        return -1;

    uint16_t top_distance = message_number - g->group[peer_index].top_lossy_number;

    if (top_distance >= MAX_LOSSY_COUNT) {
        sodium_memzero(g->group[peer_index].recv_lossy, sizeof(g->group[peer_index].recv_lossy));
        g->group[peer_index].top_lossy_number = message_number;
        g->group[peer_index].bottom_lossy_number = (message_number - MAX_LOSSY_COUNT) + 1;
        g->group[peer_index].recv_lossy[message_number % MAX_LOSSY_COUNT] = 1;
        return 0;
    }

    if (top_distance < MAX_LOSSY_COUNT) {
        unsigned int i;

        for (i = g->group[peer_index].bottom_lossy_number; i != (g->group[peer_index].bottom_lossy_number + top_distance);
                ++i) {
            g->group[peer_index].recv_lossy[i % MAX_LOSSY_COUNT] = 0;
        }

        g->group[peer_index].top_lossy_number = message_number;
        g->group[peer_index].bottom_lossy_number = (message_number - MAX_LOSSY_COUNT) + 1;
        g->group[peer_index].recv_lossy[message_number % MAX_LOSSY_COUNT] = 1;
        return 0;
    }

    return -1;
}