#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int threads; } ;
struct TYPE_6__ {int /*<<< orphan*/  message; } ;
typedef  TYPE_1__ GError ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  FALSE ; 
 int MIN (long,long) ; 
 int /*<<< orphan*/  TICK_N (char*) ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_CONF ; 
 TYPE_5__ config ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_error_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_thread_pool_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  g_thread_pool_set_max_idle_time (int) ; 
 int /*<<< orphan*/  g_thread_pool_set_max_threads (int /*<<< orphan*/ ,int,TYPE_1__**) ; 
 int /*<<< orphan*/  g_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rofi_view_call_thread ; 
 long sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpool ; 

void rofi_view_workers_initialize ( void )
{
    TICK_N ( "Setup Threadpool, start" );
    if ( config.threads == 0 ) {
        config.threads = 1;
        long procs = sysconf ( _SC_NPROCESSORS_CONF );
        if ( procs > 0 ) {
            config.threads = MIN ( procs, 128l );
        }
    }
    // Create thread pool
    GError *error = NULL;
    tpool = g_thread_pool_new ( rofi_view_call_thread, NULL, config.threads, FALSE, &error );
    if ( error == NULL ) {
        // Idle threads should stick around for a max of 60 seconds.
        g_thread_pool_set_max_idle_time ( 60000 );
        // We are allowed to have
        g_thread_pool_set_max_threads ( tpool, config.threads, &error );
    }
    // If error occurred during setup of pool, tell user and exit.
    if ( error != NULL ) {
        g_warning ( "Failed to setup thread pool: '%s'", error->message );
        g_error_free ( error );
        exit ( EXIT_FAILURE );
    }
    TICK_N ( "Setup Threadpool, done" );
}