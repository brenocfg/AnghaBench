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
typedef  int /*<<< orphan*/  pthread_mutex_t ;

/* Variables and functions */
 int CRYPTO_num_locks () ; 
 int /*<<< orphan*/  CRYPTO_set_id_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_set_locking_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * curl_locks ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self ; 
 int /*<<< orphan*/  seafile_curl_locking_callback ; 

void seafile_curl_init()
{
    int i;
    curl_locks = malloc (sizeof(pthread_mutex_t) * CRYPTO_num_locks());
    for (i = 0; i < CRYPTO_num_locks(); ++i) {
        pthread_mutex_init (&curl_locks[i], NULL);
    }

#ifndef WIN32
    /* On Windows it's better to use the default id_function.
     * As per http://linux.die.net/man/3/crypto_set_id_callback,
     * the default id_functioin uses system's default thread
     * identifying API.
     */
    CRYPTO_set_id_callback (pthread_self);
#endif
    CRYPTO_set_locking_callback (seafile_curl_locking_callback);
}