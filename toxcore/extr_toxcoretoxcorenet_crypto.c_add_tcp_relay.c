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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  tcp_mutex; int /*<<< orphan*/  tcp_c; } ;
typedef  TYPE_1__ Net_Crypto ;
typedef  int /*<<< orphan*/  IP_Port ;

/* Variables and functions */
 int add_tcp_relay_global (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int add_tcp_relay(Net_Crypto *c, IP_Port ip_port, const uint8_t *public_key)
{
    pthread_mutex_lock(&c->tcp_mutex);
    int ret = add_tcp_relay_global(c->tcp_c, ip_port, public_key);
    pthread_mutex_unlock(&c->tcp_mutex);
    return ret;
}