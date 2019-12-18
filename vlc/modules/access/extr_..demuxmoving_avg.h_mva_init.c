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
struct moving_average_s {scalar_t__ i_packet; } ;

/* Variables and functions */

__attribute__((used)) static void mva_init(struct moving_average_s *m)
{
    m->i_packet = 0;
}