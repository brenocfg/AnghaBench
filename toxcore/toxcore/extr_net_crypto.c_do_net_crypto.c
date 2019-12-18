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
typedef  int /*<<< orphan*/  Net_Crypto ;

/* Variables and functions */
 int /*<<< orphan*/  do_tcp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_timedout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_crypto_packets (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unix_time_update () ; 

void do_net_crypto(Net_Crypto *c)
{
    unix_time_update();
    kill_timedout(c);
    do_tcp(c);
    send_crypto_packets(c);
}