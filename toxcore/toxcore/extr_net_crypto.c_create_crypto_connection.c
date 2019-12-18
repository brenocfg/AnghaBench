#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_6__ {scalar_t__ status; int /*<<< orphan*/  mutex; } ;
struct TYPE_5__ {size_t crypto_connections_length; int /*<<< orphan*/  connections_mutex; TYPE_3__* crypto_connections; int /*<<< orphan*/  connection_use_counter; } ;
typedef  TYPE_1__ Net_Crypto ;
typedef  int /*<<< orphan*/  Crypto_Connection ;

/* Variables and functions */
 scalar_t__ CRYPTO_CONN_NO_CONNECTION ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ realloc_cryptoconnection (TYPE_1__*,int) ; 

__attribute__((used)) static int create_crypto_connection(Net_Crypto *c)
{
    uint32_t i;

    for (i = 0; i < c->crypto_connections_length; ++i) {
        if (c->crypto_connections[i].status == CRYPTO_CONN_NO_CONNECTION)
            return i;
    }

    while (1) { /* TODO: is this really the best way to do this? */
        pthread_mutex_lock(&c->connections_mutex);

        if (!c->connection_use_counter) {
            break;
        }

        pthread_mutex_unlock(&c->connections_mutex);
    }

    int id = -1;

    if (realloc_cryptoconnection(c, c->crypto_connections_length + 1) == 0) {
        id = c->crypto_connections_length;
        ++c->crypto_connections_length;
        memset(&(c->crypto_connections[id]), 0, sizeof(Crypto_Connection));

        if (pthread_mutex_init(&c->crypto_connections[id].mutex, NULL) != 0) {
            pthread_mutex_unlock(&c->connections_mutex);
            return -1;
        }
    }

    pthread_mutex_unlock(&c->connections_mutex);
    return id;
}