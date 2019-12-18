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
struct TYPE_3__ {int /*<<< orphan*/  pools_lock; int /*<<< orphan*/  connection_pools; } ;
typedef  TYPE_1__ HttpTxPriv ;
typedef  int /*<<< orphan*/  ConnectionPool ;

/* Variables and functions */
 int /*<<< orphan*/ * connection_pool_new (char const*) ; 
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_hash_table_lookup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  g_strdup (char const*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ConnectionPool *
find_connection_pool (HttpTxPriv *priv, const char *host)
{
    ConnectionPool *pool;

    pthread_mutex_lock (&priv->pools_lock);
    pool = g_hash_table_lookup (priv->connection_pools, host);
    if (!pool) {
        pool = connection_pool_new (host);
        g_hash_table_insert (priv->connection_pools, g_strdup(host), pool);
    }
    pthread_mutex_unlock (&priv->pools_lock);

    return pool;
}