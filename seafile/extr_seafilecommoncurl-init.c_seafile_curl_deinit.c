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
 int CRYPTO_num_locks () ; 
 int /*<<< orphan*/  CRYPTO_set_id_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_set_locking_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * curl_locks ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

void seafile_curl_deinit()
{
    int i;
    CRYPTO_set_id_callback (0);
    CRYPTO_set_locking_callback (0);

    for (i = 0; i < CRYPTO_num_locks(); ++i) {
        pthread_mutex_destroy (&curl_locks[i]);
    }
    free (curl_locks);
}