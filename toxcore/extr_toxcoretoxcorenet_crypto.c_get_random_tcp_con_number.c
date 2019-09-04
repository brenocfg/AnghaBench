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
struct TYPE_3__ {int /*<<< orphan*/  tcp_mutex; int /*<<< orphan*/  tcp_c; } ;
typedef  TYPE_1__ Net_Crypto ;

/* Variables and functions */
 int get_random_tcp_onion_conn_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int get_random_tcp_con_number(Net_Crypto *c)
{
    pthread_mutex_lock(&c->tcp_mutex);
    int ret = get_random_tcp_onion_conn_number(c->tcp_c);
    pthread_mutex_unlock(&c->tcp_mutex);

    return ret;
}