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
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  tcp_mutex; int /*<<< orphan*/  tcp_c; } ;
typedef  int /*<<< orphan*/  Node_format ;
typedef  TYPE_1__ Net_Crypto ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned int tcp_copy_connected_relays (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

unsigned int copy_connected_tcp_relays(Net_Crypto *c, Node_format *tcp_relays, uint16_t num)
{
    if (num == 0)
        return 0;

    pthread_mutex_lock(&c->tcp_mutex);
    unsigned int ret = tcp_copy_connected_relays(c->tcp_c, tcp_relays, num);
    pthread_mutex_unlock(&c->tcp_mutex);

    return ret;
}