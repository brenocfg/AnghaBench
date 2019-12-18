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
 int /*<<< orphan*/  tcp_fasttmr () ; 
 int /*<<< orphan*/  tcp_slowtmr () ; 
 int test_tcp_timer ; 

__attribute__((used)) static void
test_tcp_tmr(void)
{
  tcp_fasttmr();
  if (++test_tcp_timer & 1) {
    tcp_slowtmr();
  }
}