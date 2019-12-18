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
struct mva_packet_s {int dummy; } ;
struct moving_average_s {int i_packet; struct mva_packet_s* packets; } ;

/* Variables and functions */
 int MVA_PACKETS ; 

__attribute__((used)) static struct mva_packet_s * mva_getLastPacket(struct moving_average_s *m)
{
    return m->i_packet > 0 ? &m->packets[(m->i_packet - 1) % MVA_PACKETS] : NULL;
}