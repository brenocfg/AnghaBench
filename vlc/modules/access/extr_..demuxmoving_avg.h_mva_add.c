#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* vlc_tick_t ;
struct moving_average_s {size_t i_packet; TYPE_1__* packets; } ;
struct TYPE_2__ {void* diff; void* duration; void* dts; } ;

/* Variables and functions */
 size_t MVA_PACKETS ; 

__attribute__((used)) static void mva_add(struct moving_average_s *m,
                     vlc_tick_t dts, vlc_tick_t duration)
{
    m->packets[m->i_packet % MVA_PACKETS].dts = dts;
    m->packets[m->i_packet % MVA_PACKETS].duration = duration;
    m->packets[m->i_packet % MVA_PACKETS].diff = duration; /* will erase, last one */
    m->i_packet++;
}