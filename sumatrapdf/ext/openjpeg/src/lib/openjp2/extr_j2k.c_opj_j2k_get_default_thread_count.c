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
 int atoi (char const*) ; 
 char* getenv (char*) ; 
 int opj_get_num_cpus () ; 
 int /*<<< orphan*/  opj_has_thread_support () ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int opj_j2k_get_default_thread_count(void)
{
#if defined(MUTEX_win32) || defined(MUTEX_pthread)
    const char* num_threads_str = getenv("OPJ_NUM_THREADS");
    int num_cpus;
    int num_threads;

    if (num_threads_str == NULL || !opj_has_thread_support()) {
        return 0;
    }
    num_cpus = opj_get_num_cpus();
    if (strcmp(num_threads_str, "ALL_CPUS") == 0) {
        return num_cpus;
    }
    if (num_cpus == 0) {
        num_cpus = 32;
    }
    num_threads = atoi(num_threads_str);
    if (num_threads < 0) {
        num_threads = 0;
    } else if (num_threads > 2 * num_cpus) {
        num_threads = 2 * num_cpus;
    }
    return num_threads;
#else
    return 0;
#endif
}