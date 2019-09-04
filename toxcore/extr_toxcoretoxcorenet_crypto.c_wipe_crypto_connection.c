#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;
struct TYPE_7__ {scalar_t__ status; int /*<<< orphan*/  mutex; } ;
struct TYPE_6__ {int crypto_connections_length; TYPE_3__* crypto_connections; } ;
typedef  TYPE_1__ Net_Crypto ;
typedef  int /*<<< orphan*/  Crypto_Connection ;

/* Variables and functions */
 scalar_t__ CRYPTO_CONN_NO_CONNECTION ; 
 scalar_t__ crypt_connection_id_not_valid (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  realloc_cryptoconnection (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sodium_memzero (TYPE_3__*,int) ; 

__attribute__((used)) static int wipe_crypto_connection(Net_Crypto *c, int crypt_connection_id)
{
    if (crypt_connection_id_not_valid(c, crypt_connection_id))
        return -1;

    uint32_t i;

    /* Keep mutex, only destroy it when connection is realloced out. */
    pthread_mutex_t mutex = c->crypto_connections[crypt_connection_id].mutex;
    sodium_memzero(&(c->crypto_connections[crypt_connection_id]), sizeof(Crypto_Connection));
    c->crypto_connections[crypt_connection_id].mutex = mutex;

    for (i = c->crypto_connections_length; i != 0; --i) {
        if (c->crypto_connections[i - 1].status == CRYPTO_CONN_NO_CONNECTION) {
            pthread_mutex_destroy(&c->crypto_connections[i - 1].mutex);
        } else {
            break;
        }
    }

    if (c->crypto_connections_length != i) {
        c->crypto_connections_length = i;
        realloc_cryptoconnection(c, c->crypto_connections_length);
    }

    return 0;
}