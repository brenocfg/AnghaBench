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

/* Variables and functions */
 int tcp_next_iss () ; 
 int /*<<< orphan*/  tcp_remove_all () ; 
 int tcp_ticks ; 
 scalar_t__ test_tcp_timer ; 

__attribute__((used)) static void
tcp_setup(void)
{
  /* reset iss to default (6510) */
  tcp_ticks = 0;
  tcp_ticks = 0 - (tcp_next_iss() - 6510);
  tcp_next_iss();
  tcp_ticks = 0;

  test_tcp_timer = 0;
  tcp_remove_all();
}