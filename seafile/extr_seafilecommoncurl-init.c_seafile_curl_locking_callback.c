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
 int CRYPTO_LOCK ; 
 int /*<<< orphan*/ * curl_locks ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void seafile_curl_locking_callback(int mode, int n, const char* file, int line)
{
    if (mode & CRYPTO_LOCK) {
        pthread_mutex_lock (&curl_locks[n]);
    } else {
        pthread_mutex_unlock (&curl_locks[n]);
    }
}